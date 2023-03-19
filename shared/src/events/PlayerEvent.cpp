#include "Event.h"

// clang-format off
static js::Event playerAnimationChangeEvent(alt::CEvent::Type::PLAYER_CHANGE_ANIMATION_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerChangeAnimationEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("oldAnimDict", e->GetOldAnimationDict());
    args.Set("newAnimDict", e->GetNewAnimationDict());
    args.Set("oldAnimName", e->GetNewAnimationName());
    args.Set("newAnimName", e->GetNewAnimationName());
});
