#include "Event.h"
#include "interfaces/IResource.h"
#include "magic_enum/include/magic_enum.hpp"

extern js::Class eventContextClass, cancellableEventContextClass;

js::Promise js::Event::CallEventBinding(bool custom, int type, EventArgs& args, IResource* resource)
{
    v8::Isolate* isolate = resource->GetIsolate();
    v8::Local<v8::Context> context = resource->GetContext();
    js::Function onEvent = resource->GetBindingExport<v8::Function>(BindingExport::ON_EVENT);
    if(!onEvent.IsValid()) return js::Promise{ v8::Local<v8::Promise>() };

    std::optional<v8::Local<v8::Value>> result = onEvent.Call<v8::Local<v8::Value>>(custom, type, args.Get());
    return js::Promise{ result.value_or(v8::Local<v8::Value>()).As<v8::Promise>() };
}

void js::Event::SendEvent(const alt::CEvent* ev, IResource* resource)
{
    Event* eventHandler = GetEventHandler(ev->GetType());
    if(!eventHandler) return;

    EventArgs eventArgs;
    if(ev->IsCancellable()) eventArgs = cancellableEventContextClass.Create(resource->GetContext(), (void*)ev);
    else
        eventArgs = eventContextClass.Create(resource->GetContext(), (void*)ev);

    eventHandler->argsCb(ev, eventArgs);

    js::Promise promise = CallEventBinding(false, (int)ev->GetType(), eventArgs, resource);
    eventArgs.Get()->SetAlignedPointerInInternalField(1, nullptr);
    if(!promise.IsValid()) return;
    if(ev->GetType() == alt::CEvent::Type::RESOURCE_STOP && static_cast<const alt::CResourceStopEvent*>(ev)->GetResource() == resource->GetResource()) promise.Await();
}

void js::Event::SendEvent(EventType type, EventArgs& args, IResource* resource)
{
    js::Promise promise = CallEventBinding(true, (int)type, args, resource);
    if(!promise.IsValid()) return;
}

// Class
static void CancelEventCallback(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CCancellableEvent* ev = ctx.GetExtraInternalFieldValue<alt::CCancellableEvent>();
    if(ev->WasCancelled()) return;
    ev->Cancel();
}
static void IsCancelledGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CCancellableEvent* ev = ctx.GetExtraInternalFieldValue<alt::CCancellableEvent>();
    ctx.Return(ev->WasCancelled());
}
static void TypeGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CEvent* ev = ctx.GetExtraInternalFieldValue<alt::CEvent>();
    ctx.Return(ev->GetType());
}

static void IsCancellableGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::CEvent* ev = ctx.GetExtraInternalFieldValue<alt::CEvent>();
    ctx.Return(ev->IsCancellable());
}

// clang-format off
extern js::Class eventContextClass("EventContext", [](js::ClassTemplate& tpl) {
    tpl.LazyProperty("type", TypeGetter);
    tpl.LazyProperty("isCancellable", IsCancellableGetter);
}, true);

extern class js::Class cancellableEventContextClass("CancellableEventContext", &eventContextClass, [](js::ClassTemplate& tpl) {
    tpl.BoundMethod("cancel", CancelEventCallback);
    tpl.Property("isCancelled", IsCancelledGetter);
}, true);
