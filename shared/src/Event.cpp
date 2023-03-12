#include "Event.h"
#include "interfaces/IResource.h"
#include "magic_enum/include/magic_enum.hpp"

void js::Event::CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    v8::Local<v8::Function> onEvent = resource->GetBindingExport<v8::Function>("events:onEvent");
    if(onEvent.IsEmpty()) return;

    std::array<v8::Local<v8::Value>, 3> funcArgs = { js::JSValue(custom), js::JSValue(type), args.Get() };
    onEvent->Call(context, v8::Undefined(isolate), funcArgs.size(), funcArgs.data());
}

void js::Event::CancelEventCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    alt::CEvent* ev = static_cast<alt::CEvent*>(info.Data().As<v8::External>()->Value());
    if(ev->WasCancelled()) return;
    ev->Cancel();
    js::Object thisObj{ info.This() };
    thisObj.Set("cancelled", true);
}

v8::Local<v8::Function> js::Event::GetCancelFunction(js::IResource* resource, const alt::CEvent* ev)
{
    v8::Local<v8::Function> func = v8::Function::New(resource->GetContext(), CancelEventCallback, v8::External::New(resource->GetIsolate(), (void*)ev)).ToLocalChecked();
    func->SetName(js::JSValue("cancel"));
    return func;
}

void js::Event::SendEvent(const alt::CEvent* ev, IResource* resource)
{
    Event* eventHandler = GetEventHandler(ev->GetType());
    if(!eventHandler) return;

    EventArgs eventArgs;
    eventHandler->argsCb(ev, eventArgs);
    eventArgs.Set("cancel", GetCancelFunction(resource, ev));
    eventArgs.Set("cancelled", ev->WasCancelled());

    CallEventBinding(false, (int)ev->GetType(), eventArgs, resource);
}

void js::Event::SendEvent(EventType type, EventArgs& args, IResource* resource)
{
    CallEventBinding(true, (int)type, args, resource);
}

void js::Event::RegisterEvents(js::IResource* resource)
{
    v8::Local<v8::Function> func = resource->GetBindingExport<v8::Function>("events:setEvents");
    if(func.IsEmpty()) return;

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
}
