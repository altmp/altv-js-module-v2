#include "Event.h"

// clang-format off
static js::Event gameEntityCreateEvent(alt::CEvent::Type::GAME_ENTITY_CREATE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGameEntityCreateEvent*>(ev);
    args.Set("entity", e->GetTarget());
});

static js::Event gameEntityDestroyEvent(alt::CEvent::Type::GAME_ENTITY_DESTROY, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CGameEntityDestroyEvent*>(ev);
    args.Set("entity", e->GetTarget());
});

static js::Event webViewEvent(alt::CEvent::Type::WEB_VIEW_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWebViewEvent*>(ev);
    args.Set("target", e->GetTarget());
    args.Set("name", e->GetName());
    args.Set("args", e->GetArgs());
});

static js::Event rmluiEvent(alt::CEvent::Type::RMLUI_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CRmlEvent*>(ev);
    args.Set("target", e->GetElement());
    args.Set("name", e->GetName());
    args.Set("args", e->GetArgs());
});
