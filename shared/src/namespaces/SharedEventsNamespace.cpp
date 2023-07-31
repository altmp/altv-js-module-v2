#include "Namespace.h"
#include "interfaces/IResource.h"
#include "helpers/ValueBuffer.h"

static void RawEmitEnabledGetter(js::PropertyContext& ctx)
{
    ctx.Return(ctx.GetResource()->IsRawEmitEnabled());
}

static void RawEmitEnabledSetter(js::PropertyContext& ctx)
{
    bool value;
    if(!ctx.GetValue(value)) return;

    ctx.GetResource()->ToggleRawEmit(value);
}

static void Emit(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    js::IResource* resource = ctx.GetResource();

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 1);
    alt::MValue val;
    for(int i = 1; i < ctx.GetArgCount(); i++)
    {
        if(resource->IsRawEmitEnabled())
        {
            v8::Local<v8::Value> arg;
            if(!ctx.GetArg(i, arg)) continue;
            alt::MValueByteArray result = js::JSToRawBytes(arg, resource);
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 1))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerLocalEvent(eventName, args);
}

// clang-format off
extern js::Namespace sharedEventsNamespace("Events", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("rawEmitEnabled", RawEmitEnabledGetter, RawEmitEnabledSetter);

    tpl.StaticFunction("emit", Emit);
});
