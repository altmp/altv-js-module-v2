#include "Event.h"
#include "cpp-sdk/events/CServerStartedEvent.h"

// clang-format off
static js::Event serverStartedEvent(alt::CEvent::Type::SERVER_STARTED, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
});
