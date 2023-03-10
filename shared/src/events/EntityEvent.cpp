#include "Event.h"

// clang-format off
static js::Event baseObjectCreateEvent(alt::CEvent::Type::CREATE_BASE_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CCreateBaseObjectEvent*>(ev);
    args.Set("object", e->GetObject());
});

static js::Event baseObjectRemoveEvent(alt::CEvent::Type::REMOVE_BASE_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CRemoveBaseObjectEvent*>(ev);
    args.Set("object", e->GetObject());
});
