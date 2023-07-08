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

static js::Event playerStartEnterVehicle(alt::CEvent::Type::PLAYER_START_ENTER_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerStartEnterVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});

static js::Event playerStartLeaveVehicle(alt::CEvent::Type::PLAYER_START_LEAVE_VEHICLE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);
    args.Set("player", e->GetPlayer());
    args.Set("vehicle", e->GetTarget());
    args.Set("seat", e->GetSeat());
});
