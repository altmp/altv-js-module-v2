#include "Event.h"

// clang-format off
static js::Event serverStartedEvent(alt::CEvent::Type::PLAYER_CONNECT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CPlayerConnectEvent*>(ev);

    args.Set("player", e->GetTarget());
    // args.Set("reason", e->GetReason());
});
