#include "Namespace.h"
#include "interfaces/IResource.h"

static void EmitServer(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;
    js::IResource* resource = ctx.GetResource();

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

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
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerServerEvent(eventName, args);
}

static void EmitServerUnreliable(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;
    js::IResource* resource = ctx.GetResource();

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

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
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerServerEventUnreliable(eventName, args);
}

static void EmitServerRPC(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    js::Array arr;
    if (!ctx.GetArg(1, arr)) return;


    alt::MValueArgs args;
    for(int i = 0; i < arr.Length; ++i)
    {
        alt::MValue val;
        if(!arr.Get(i, val)) continue;

        args.push_back(val);
    }

    ctx.Return(alt::ICore::Instance().TriggerServerRPCEvent(eventName, args));
}

// clang-format off
extern js::Namespace sharedEventsNamespace;
extern js::Namespace eventsNamespace("Events", &sharedEventsNamespace, [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("emitServer", &EmitServer);
    tpl.StaticFunction("emitServerUnreliable", &EmitServerUnreliable);

    tpl.StaticFunction("emitServerRPC", &EmitServerRPC);
});
