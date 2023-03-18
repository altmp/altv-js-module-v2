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

    args.Set("victim", e->GetTarget());
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

static js::Event playerEnteredVehicleEvent(alt::CEvent::Type::PLAYER_ENTER_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerVehicleEnteringEvent(alt::CEvent::Type::PLAYER_ENTERING_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerEnteringVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerVehicleLeftEvent(alt::CEvent::Type::PLAYER_LEAVE_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerVehicleSeatChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeVehicleSeatEvent*>(ev);

    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("oldSeat", e->GetOldSeat());
    args.Set("newSeat", e->GetNewSeat());
});

static js::Event playerWeaponChangeEvent(alt::CEvent::Type::PLAYER_WEAPON_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerWeaponChangeEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldSeat", e->GetOldWeapon());
    args.Set("newSeat", e->GetNewWeapon());
});

static js::Event localMetaChangeEvent(alt::CEvent::Type::LOCAL_SYNCED_META_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CLocalMetaDataChangeEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("key", e->GetKey());
    args.Set("oldValue", e->GetOldVal());
    args.Set("newValue", e->GetVal());
});

// TODO
static js::Event connectionQueueAddEvent(alt::CEvent::Type::CONNECTION_QUEUE_ADD, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConnectionQueueAddEvent*>(ev);
});

// TODO
static js::Event connectionQueueRemoveEvent(alt::CEvent::Type::CONNECTION_QUEUE_REMOVE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConnectionQueueRemoveEvent*>(ev);
});

static js::Event requestControlEvent(alt::CEvent::Type::PLAYER_REQUEST_CONTROL, [](const alt::CEvent* ev, js::Event::EventArgs& args)
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

static js::Event playerAnimationChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_ANIMATION_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeAnimationEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldAnimDict", e->GetOldAnimationDict());
    args.Set("newAnimDict", e->GetNewAnimationDict());
    args.Set("oldAnimName", e->GetNewAnimationName());
    args.Set("newAnimName", e->GetNewAnimationName());
});