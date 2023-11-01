#include "Event.h"

// clang-format off
static js::Event playerWeaponShootEvent(alt::CEvent::Type::PLAYER_WEAPON_SHOOT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerWeaponShootEvent*>(ev);
    args.Set("weapon", e->GetWeapon());
    args.Set("totalAmmo", e->GetTotalAmmo());
    args.Set("ammoInClip", e->GetAmmoInClip());
});

static js::Event playerBulletHitEvent(alt::CEvent::Type::PLAYER_BULLET_HIT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerBulletHitEvent*>(ev);
    args.Set("weapon", e->GetWeapon());
    args.Set("victim", e->GetVictim());
    args.Set("pos", e->GetPosition());
});

static js::Event playerStartVehicleEnter(alt::CEvent::Type::PLAYER_START_ENTER_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerStartEnterVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerStartVehicleLeave(alt::CEvent::Type::PLAYER_START_LEAVE_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerEnterVehicle(alt::CEvent::Type::PLAYER_ENTER_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerLeaveVehicle(alt::CEvent::Type::PLAYER_LEAVE_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerWeaponChangeEvent(alt::CEvent::Type::PLAYER_WEAPON_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerWeaponChangeEvent*>(ev);
    args.Set("oldWeapon", e->GetOldWeapon());
    args.Set("newWeapon", e->GetNewWeapon());
});
