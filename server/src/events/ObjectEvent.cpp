#include "Event.h"

// clang-format off
static js::Event clientDeleteObjectEvent(alt::CEvent::Type::CLIENT_DELETE_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientDeleteObjectEvent*>(ev);

    args.Set("player", e->GetTarget());
});

static js::Event clientRequestObjectEvent(alt::CEvent::Type::CLIENT_REQUEST_OBJECT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientRequestObjectEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("model", e->GetModel());
    args.Set("pos", e->GetPosition());
});
