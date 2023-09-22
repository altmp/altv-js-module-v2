#include "Event.h"

// clang-format off
static js::Event pedDeathEvent(alt::CEvent::Type::PED_DEATH, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPedDeathEvent*>(ev);

    args.Set("ped", e->GetTarget());
    args.Set("killer", e->GetKiller());
    args.Set("weapon", e->GetWeapon());
});

static js::Event pedDamageEvent(alt::CEvent::Type::PED_DAMAGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPedDamageEvent*>(ev);

    args.Set("ped", e->GetTarget());
    args.Set("attacker", e->GetAttacker());
    args.Set("healthDamage", e->GetHealthDamage());
    args.Set("armourDamage", e->GetArmourDamage());
    args.Set("weapon", e->GetWeapon());
});
