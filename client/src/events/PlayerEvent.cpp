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
