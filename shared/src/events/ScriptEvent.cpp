#include "Event.h"

// clang-format off
static js::Event clientScriptEvent(alt::CEvent::Type::CLIENT_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

#ifdef ALT_SERVER_API
    args.Set("player", e->GetTarget());
#endif

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.size());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray);
});

static js::Event serverScriptEvent(alt::CEvent::Type::SERVER_SCRIPT_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CServerScriptEvent*>(ev);
    args.Set("eventName", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    js::Array argsArray(eventArgs.size());
    js::MValueArgsToJS(eventArgs, argsArray);
    args.Set("args", argsArray);
});
