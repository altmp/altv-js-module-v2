#include "Event.h"

// clang-format off
static js::Event playerConnectEvent(alt::CEvent::Type::PLAYER_CONNECT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerConnectEvent*>(ev);

    args.Set("player", e->GetTarget());
    // args.Set("reason", e->GetReason());
});

static js::Event playerConnectDeniedEvent(alt::CEvent::Type::PLAYER_CONNECT_DENIED, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerConnectDeniedEvent*>(ev);

    args.Set("reason", e->GetReason());
    args.Set("name", e->GetName());
    args.Set("ip", e->GetIp());
    args.Set("passwordHash", e->GetPasswordHash());
    args.Set("isDebug", e->IsDebug());
    args.Set("branch", e->GetBranch());
    args.Set("version", e->GetMajorVersion());
    args.Set("cdnUrl", e->GetCdnUrl());
    args.Set("discordId", e->GetDiscordId());
});

static js::Event playerDisconnectEvent(alt::CEvent::Type::PLAYER_DISCONNECT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerDisconnectEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("reason", e->GetReason());
});

static js::Event playerDamageEvent(alt::CEvent::Type::PLAYER_DAMAGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerDamageEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("attacker", e->GetAttacker());
    args.Set("healthDamage", e->GetHealthDamage());
    args.Set("armourDamage", e->GetArmourDamage());
    args.Set("weaponHash", e->GetWeapon());
});

static js::Event playerDeathEvent(alt::CEvent::Type::PLAYER_DEATH, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerDeathEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("killer", e->GetKiller());
    args.Set("weaponHash", e->GetWeapon());
});

static js::Event playerRequestControlEvent(alt::CEvent::Type::PLAYER_REQUEST_CONTROL, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerRequestControlEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("target", e->GetTarget());
});

static js::Event playerInteriorChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_INTERIOR_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeInteriorEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldInterior", e->GetOldInteriorLocation());
    args.Set("newInterior", e->GetNewInteriorLocation());
});

static js::Event playerDimensionChangeEvent(alt::CEvent::Type::PLAYER_DIMENSION_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerDimensionChangeEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldDimension", e->GetOldDimension());
    args.Set("newDimension", e->GetNewDimension());
});

static js::Event playerWeaponChangeEvent(alt::CEvent::Type::PLAYER_WEAPON_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerWeaponChangeEvent*>(ev);
    args.Set("player", e->GetTarget());
    args.Set("oldWeapon", e->GetOldWeapon());
    args.Set("newWeapon", e->GetNewWeapon());
});

static js::Event requestSyncedSceneEvent(alt::CEvent::Type::REQUEST_SYNCED_SCENE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CRequestSyncedSceneEvent*>(ev);

    args.Set("player", e->GetSource());
    args.Set("sceneID", e->GetSceneID());
});

static js::Event startSyncedSceneEvent(alt::CEvent::Type::START_SYNCED_SCENE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CStartSyncedSceneEvent*>(ev);

    args.Set("player", e->GetSource());
    args.Set("sceneID", e->GetSceneID());
    args.Set("startPos", e->GetStartPosition());
    args.Set("startRot", e->GetStartRotation());
    args.Set("animDict", e->GetAnimDictHash());

    js::Array arr;
    for(auto& [entity, animHash] : e->GetEntityAndAnimHashPairs())
    {
        js::Object obj;
        obj.Set("entity", entity.get());
        obj.Set("animHash", animHash);
        arr.Push(obj);
    }
    args.Set("entityAndAnimHashPairs", arr);
});

static js::Event stopSyncedSceneEvent(alt::CEvent::Type::STOP_SYNCED_SCENE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CStopSyncedSceneEvent*>(ev);

    args.Set("player", e->GetSource());
    args.Set("sceneID", e->GetSceneID());
});

static js::Event updateSyncedSceneEvent(alt::CEvent::Type::UPDATE_SYNCED_SCENE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CUpdateSyncedSceneEvent*>(ev);

    args.Set("player", e->GetSource());
    args.Set("sceneID", e->GetSceneID());
    args.Set("startRate", e->GetStartRate());
});
