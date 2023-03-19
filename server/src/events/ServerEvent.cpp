#include "Event.h"
#include "cpp-sdk/events/CServerStartedEvent.h"

// clang-format off
static js::Event serverStartedEvent(alt::CEvent::Type::SERVER_STARTED, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
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
