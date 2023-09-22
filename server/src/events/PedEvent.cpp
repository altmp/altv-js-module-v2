#include "Event.h"

// clang-format off
static js::Event pedHealEvent(alt::CEvent::Type::PED_HEAL, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPedHealEvent*>(ev);

    args.Set("ped", e->GetTarget());
    args.Set("newHealth", e->GetNewHealth());
    args.Set("oldHealth", e->GetOldHealth());

    args.Set("newArmour", e->GetNewArmour());
    args.Set("oldArmour", e->GetOldArmour());
});
