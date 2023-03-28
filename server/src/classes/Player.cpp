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

static void CurrentWeaponGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetCurrentWeapon());
}

static void CurrentWeaponSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetValueAsHash(weapon)) return;

    player->SetCurrentWeapon(weapon);
}

static void SendNamesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    ctx.Return(player->GetSendNames());
}

static void SendNamesSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    bool state;
    if(!ctx.GetValue(state)) return;

    player->SetSendNames(state);
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

static void EmitUnreliable(js::FunctionContext& ctx)
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
    alt::ICore::Instance().TriggerClientEventUnreliable(player, eventName, args);
}

static void SetWeaponTintIndex(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint8_t tintIndex;
    if(!ctx.GetArg(1, tintIndex)) return;

    player->SetWeaponTintIndex(weapon, tintIndex);
}

static void AddWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint32_t component;
    if(!ctx.GetArgAsHash(1, component)) return;

    player->AddWeaponComponent(weapon, component);
}

static void RemoveWeaponComponent(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint32_t component;
    if(!ctx.GetArgAsHash(1, component)) return;

    player->RemoveWeaponComponent(weapon, component);
}

static void GiveWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2, 3)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    uint16_t ammo;
    if(!ctx.GetArg(1, ammo)) return;

    bool selectWeapon = false;
    if(ctx.GetArgCount() == 3)
    {
        if(!ctx.GetArg(2, selectWeapon)) return;
    }

    player->GiveWeapon(weapon, ammo, selectWeapon);
}

static void RemoveWeapon(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;

    alt::IPlayer* player = ctx.GetThisObject<alt::IPlayer>();

    uint32_t weapon;
    if(!ctx.GetArgAsHash(0, weapon)) return;

    player->RemoveWeapon(weapon);
}

static void LocalMetaGetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    ctx.Return(player->GetLocalMetaData(ctx.GetProperty()));
}

static void LocalMetaSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    alt::MValue value;
    if(!ctx.GetValue(value)) return;

    player->SetLocalMetaData(ctx.GetProperty(), value);
}

static void LocalMetaDeleter(js::DynamicPropertyContext<v8::Boolean>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    if(!player->HasLocalMetaData(ctx.GetProperty()))
    {
        ctx.Return(false);
        return;
    }

    player->DeleteLocalMetaData(ctx.GetProperty());
    ctx.Return(true);
}

static void LocalMetaEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IPlayer* player = ctx.GetParent<alt::IPlayer>();

    ctx.Return(player->GetLocalMetaDataKeys());
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.Property<alt::IPlayer, &alt::IPlayer::IsConnected>("isConnected");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetPing>("ping");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetIP>("ip");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetSocialID>("socialId");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetHwidHash>("hwidHash");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetHwidExHash>("hwidExHash");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetAuthToken>("authToken");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetDiscordId>("discordId");
    tpl.Property("model", &ModelGetter, &ModelSetter);
    tpl.Property<alt::IPlayer, uint16_t, &alt::IPlayer::GetArmour, &alt::IPlayer::SetArmour>("armour");
    tpl.Property<alt::IPlayer, uint16_t, &alt::IPlayer::GetMaxArmour, &alt::IPlayer::SetMaxArmour>("maxArmour");
    tpl.Property("currentWeapon", &CurrentWeaponGetter, &CurrentWeaponSetter);
    tpl.Property<alt::IPlayer, uint16_t, &alt::IPlayer::GetHealth, &alt::IPlayer::SetHealth>("health");
    tpl.Property<alt::IPlayer, uint16_t, &alt::IPlayer::GetMaxHealth, &alt::IPlayer::SetMaxHealth>("maxHealth");
    tpl.Property<alt::IPlayer, bool, &alt::IPlayer::GetInvincible, &alt::IPlayer::SetInvincible>("invincible");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetWeapons>("weapons");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetInteriorLocation>("interiorLocation");
    tpl.Property<alt::IPlayer, &alt::IPlayer::GetLastDamagedBodyPart>("lastDamagedBodyPart");
    tpl.Property("sendNames", &SendNamesGetter, &SendNamesSetter);

    tpl.Method("emit", &Emit);
    tpl.Method("emitUnreliable", &EmitUnreliable);
    tpl.Method<alt::IPlayer, void, alt::Position, uint32_t, &alt::IPlayer::Spawn>("spawn");
    tpl.Method<alt::IPlayer, void, &alt::IPlayer::Despawn>("despawn");
    tpl.Method("setWeaponTintIndex", &SetWeaponTintIndex);
    tpl.Method("addWeaponComponent", &AddWeaponComponent);
    tpl.Method("removeWeaponComponent", &RemoveWeaponComponent);
    tpl.Method<alt::IPlayer, void, &alt::IPlayer::ClearBloodDamage>("clearBloodDamage");
    tpl.Method("giveWeapon", &GiveWeapon);
    tpl.Method("removeWeapon", &RemoveWeapon);
    tpl.Method<alt::IPlayer, void, &alt::IPlayer::RemoveAllWeapons>("removeAllWeapons");
    tpl.Method<alt::IPlayer, void, int, int, int, int, int, int, &alt::IPlayer::SetDateTime>("setDateTime");
    tpl.Method<alt::IPlayer, void, uint32_t, &alt::IPlayer::SetWeather>("setWeather");
    tpl.Method<alt::IPlayer, void, const std::string&, &alt::IPlayer::Kick>("kick");
    // todo: clothes and props methods
    tpl.Method<alt::IPlayer, bool, uint16_t, &alt::IPlayer::IsEntityInStreamingRange>("isEntityInStreamingRange");
    tpl.Method<alt::IPlayer, void, alt::IVehicle*, uint8_t, &alt::IPlayer::SetIntoVehicle>("setIntoVehicle");
    tpl.Method<alt::IPlayer, void, const std::string&, const std::string&, uint32_t, &alt::IPlayer::PlayAmbientSpeech>("playAmbientSpeech");
    // todo: appearance methods

    tpl.DynamicProperty("localMeta", LocalMetaGetter, LocalMetaSetter, LocalMetaDeleter, LocalMetaEnumerator);

    tpl.StaticFunction("getByID", &GetByID);
});
