#include "Event.h"
#include "interfaces/IResource.h"
#include "magic_enum/include/magic_enum.hpp"

v8::Local<v8::Function> js::Event::GetResourceBinding(IResource* resource)
{
    auto& resourceBindingMap = GetResourceBindingMap();
    auto it = resourceBindingMap.find(resource);
    if(it == resourceBindingMap.end()) return v8::Local<v8::Function>();
    return it->second.Get(resource->GetIsolate());
}

void js::Event::CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    v8::Local<v8::Function> func = GetResourceBinding(resource);

    std::array<v8::Local<v8::Value>, 3> funcArgs = { js::JSValue(custom), js::JSValue(type), args.Get() };
    func->Call(context, v8::Undefined(isolate), funcArgs.size(), funcArgs.data());
}

void js::Event::SendEvent(const alt::CEvent* ev, IResource* resource)
{
    Event* eventHandler = GetEventHandler(ev->GetType());
    if(!eventHandler) return;

    EventArgs eventArgs;
    eventHandler->argsCb(ev, eventArgs);

    CallEventBinding(false, (int)ev->GetType(), eventArgs, resource);
}

void js::Event::SendEvent(EventType type, EventArgs& args, IResource* resource)
{
    CallEventBinding(true, (int)type, args, resource);
}

void js::Event::RegisterEvents(js::IResource* resource)
{
    v8::Local<v8::Value> val = resource->GetBindingExport("events:setEvents");
    if(val.IsEmpty() || !val->IsFunction()) return;
    v8::Local<v8::Function> func = val.As<v8::Function>();

    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    v8::Local<v8::Object> eventsObj = v8::Object::New(isolate);
    v8::Local<v8::Object> customEventsObj = v8::Object::New(isolate);

    auto values = magic_enum::enum_entries<alt::CEvent::Type>();
    for(int i = (int)alt::CEvent::Type::NONE + 1; i < (int)alt::CEvent::Type::ALL; i++)
    {
        auto& entry = values[i];
        eventsObj->Set(context, js::JSValue((int)entry.first), js::JSValue(entry.second.data()));
    }
    auto customValues = magic_enum::enum_entries<js::EventType>();
    for(int i = (int)js::EventType::NONE + 1; i < (int)js::EventType::SIZE; i++)
    {
        auto& entry = customValues[i];
        customEventsObj->Set(context, js::JSValue((int)entry.first), js::JSValue(entry.second.data()));
    }

    std::vector<v8::Local<v8::Value>> args = { eventsObj, customEventsObj };
    func->Call(context, v8::Undefined(isolate), args.size(), args.data());

    // Cache onEvent binding
    v8::Local<v8::Value> onEventVal = resource->GetBindingExport("events:onEvent");
    if(val.IsEmpty() || !val->IsFunction()) return;
    v8::Local<v8::Function> onEventFunc = onEventVal.As<v8::Function>();
    GetResourceBindingMap().insert({ resource, Persistent<v8::Function>(isolate, onEventFunc) });
}

void js::Event::UnregisterEvents(IResource* resource)
{
    GetResourceBindingMap().erase(resource);
}
