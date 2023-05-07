#include "Event.h"
#include "interfaces/IResource.h"
#include "magic_enum/include/magic_enum.hpp"

js::Promise js::Event::CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    js::Function onEvent = resource->GetBindingExport<v8::Function>("events:onEvent");
    if(!onEvent.IsValid()) return js::Promise{ v8::Local<v8::Promise>() };

    std::optional<v8::Local<v8::Value>> result = onEvent.Call<v8::Local<v8::Value>>(custom, type, args.Get());
    return js::Promise{ result.value_or(v8::Local<v8::Value>()).As<v8::Promise>() };
}

void js::Event::CancelEventCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    alt::CEvent* ev = static_cast<alt::CEvent*>(info.Data().As<v8::External>()->Value());
    if(ev->WasCancelled()) return;
    ev->Cancel();
    js::Object thisObj{ info.This() };
    thisObj.Set("isCancelled", true);
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
    eventArgs.Set("isCancelled", ev->WasCancelled());
    eventArgs.Freeze();

    js::Promise promise = CallEventBinding(false, (int)ev->GetType(), eventArgs, resource);
    if(!promise.IsValid()) return;
    if(ev->GetType() == alt::CEvent::Type::RESOURCE_STOP) promise.Await();
}

void js::Event::SendEvent(EventType type, EventArgs& args, IResource* resource)
{
    js::Promise promise = CallEventBinding(true, (int)type, args, resource);
    if(!promise.IsValid()) return;
}
