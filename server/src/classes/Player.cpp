#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;
    alt::IEntity* entity = alt::ICore::Instance().GetEntityByID(id);
    if(!entity || entity->GetType() != alt::IBaseObject::Type::PLAYER) ctx.Return(nullptr);
    else
        ctx.Return((alt::IBaseObject*)entity);
}

static void ModelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();
    ctx.Return(player->GetModel());
}

static void ModelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();
    uint32_t model;
    if(!ctx.GetValueAsHash(model)) return;
    player->SetModel(model);
}

static void Emit(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1, 32)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

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
    alt::ICore::Instance().TriggerClientEvent(player, eventName, args);
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.Property("model", &ModelGetter, &ModelSetter);

    tpl.Method("emit", &Emit);
    tpl.Method<alt::IPlayer, void, alt::Position, uint32_t, &alt::IPlayer::Spawn>("spawn");

    tpl.StaticFunction("getByID", &GetByID);
});
