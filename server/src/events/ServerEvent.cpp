#include "Event.h"
#include "cpp-sdk/events/CServerStartedEvent.h"

// clang-format off
static js::Event serverStartedEvent(alt::CEvent::Type::SERVER_STARTED, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
});

static js::Event connectionQueueAddEvent(alt::CEvent::Type::CONNECTION_QUEUE_ADD, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConnectionQueueAddEvent*>(ev);

    args.Set("connectionInfo", e->GetConnectionInfo());
});

static js::Event connectionQueueRemoveEvent(alt::CEvent::Type::CONNECTION_QUEUE_REMOVE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConnectionQueueRemoveEvent*>(ev);

    args.Set("connectionInfo", e->GetConnectionInfo());
});
