#include "Namespace.h"

static void EmitAllClients(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 32)) return;

    std::string eventName;
    if(!ctx.GetArg(0, eventName)) return;

    alt::MValueArgs args;
    args.Reserve(ctx.GetArgCount() - 1);
    alt::MValue val;
    for(int i = 1; i < ctx.GetArgCount(); i++)
    {
        if(!ctx.GetArg(i, val)) continue;
        args.Push(val);
    }
    alt::ICore::Instance().TriggerClientEventForAll(eventName, args);
}

// clang-format off
extern js::Namespace sharedEventsNamespace;
extern js::Namespace eventsNamespace("Events", &sharedEventsNamespace, [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("emitAllClients", EmitAllClients);
});
