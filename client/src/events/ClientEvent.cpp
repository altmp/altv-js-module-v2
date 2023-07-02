#include "Event.h"
#include "events/CAudioEvent.h"

// clang-format off
static js::Event keyBoardEvent(alt::CEvent::Type::KEYBOARD_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CKeyboardEvent*>(ev);
    args.Set("key", e->GetKeyCode());
    args.Set("state", e->GetKeyState());
});

static js::Event webViewEvent(alt::CEvent::Type::WEB_VIEW_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWebViewEvent*>(ev);
    args.Set("target", e->GetTarget());
    args.Set("name", e->GetName());
    args.Set("args", e->GetArgs());
});

static js::Event webSocketClientEvent(alt::CEvent::Type::WEB_SOCKET_CLIENT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWebSocketClientEvent*>(ev);
    args.Set("target", e->GetTarget());
    args.Set("name", e->GetName());
    args.Set("args", e->GetArgs());
});

static js::Event audioEvent(alt::CEvent::Type::AUDIO_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CAudioEvent*>(ev);
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

static js::Event windowFocusChangeEvent(alt::CEvent::Type::WINDOW_FOCUS_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWindowFocusChangeEvent*>(ev);
    args.Set("isFocused", e->GetState());
});

static js::Event windowResolutionChangeEvent(alt::CEvent::Type::WINDOW_RESOLUTION_CHANGE, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CWindowResolutionChangeEvent*>(ev);
    args.Set("oldResolution", e->GetOldResolution());
    args.Set("newResolution", e->GetNewResolution());
});
