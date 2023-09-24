#include "Namespace.h"
#include "interfaces/IResource.h"

static void EmitPlayers(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2, 32)) return;
    js::IResource* resource = ctx.GetResource();

    js::Array playersArr;
    if(!ctx.GetArg(0, playersArr)) return;
    std::vector<alt::IPlayer*> players;
    players.reserve(playersArr.Length());
    for(int i = 0; i < playersArr.Length(); i++)
    {
        alt::IPlayer* player = playersArr.Get<alt::IPlayer*>(i);
        if(!player) continue;
        players.push_back(player);
    }

    std::string eventName;
    if(!ctx.GetArg(1, eventName)) return;

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 2);
    alt::MValue val;
    for(int i = 2; i < ctx.GetArgCount(); i++)
    {
        if(resource->IsRawEmitEnabled())
        {
            v8::Local<v8::Value> arg;
            if(!ctx.GetArg(i, arg)) continue;
            alt::MValueByteArray result = js::JSToRawBytes(arg, resource);
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 2))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEvent(players, eventName, args);
}

static void EmitPlayersUnreliable(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2, 32)) return;
    js::IResource* resource = ctx.GetResource();

    js::Array playersArr;
    if(!ctx.GetArg(0, playersArr)) return;
    std::vector<alt::IPlayer*> players;
    players.reserve(playersArr.Length());
    for(int i = 0; i < playersArr.Length(); i++)
    {
        alt::IPlayer* player = playersArr.Get<alt::IPlayer*>(i);
        if(!player) continue;
        players.push_back(player);
    }

    std::string eventName;
    if(!ctx.GetArg(1, eventName)) return;

    alt::MValueArgs args;
    args.reserve(ctx.GetArgCount() - 2);
    alt::MValue val;
    for(int i = 2; i < ctx.GetArgCount(); i++)
    {
        if(resource->IsRawEmitEnabled())
        {
            v8::Local<v8::Value> arg;
            if(!ctx.GetArg(i, arg)) continue;
            alt::MValueByteArray result = js::JSToRawBytes(arg, resource);
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 2))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEventUnreliable(players, eventName, args);
}

static void EmitAllPlayers(js::FunctionContext& ctx)
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
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 1))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEventForAll(eventName, args);
}

static void EmitAllPlayersUnreliable(js::FunctionContext& ctx)
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
            if(!ctx.Check(result.get() != nullptr, "Failed to serialize argument at index " + std::to_string(i - 1))) return;
            val = result;
        }
        else if(!ctx.GetArg(i, val))
            continue;

        args.push_back(val);
    }
    alt::ICore::Instance().TriggerClientEventUnreliableForAll(eventName, args);
}

// clang-format off
extern js::Namespace sharedEventsNamespace;
extern js::Namespace eventsNamespace("Events", &sharedEventsNamespace, [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("emitPlayers", &EmitPlayers);
    tpl.StaticFunction("emitPlayersUnreliable", &EmitPlayersUnreliable);
    tpl.StaticFunction("emitAllPlayers", &EmitAllPlayers);
    tpl.StaticFunction("emitAllPlayersUnreliable", &EmitAllPlayersUnreliable);
});
