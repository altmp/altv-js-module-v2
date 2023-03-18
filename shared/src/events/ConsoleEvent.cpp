#include "Event.h"

// clang-format off
static js::Event consoleCommandEvent(alt::CEvent::Type::CONSOLE_COMMAND_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CConsoleCommandEvent*>(ev);
    args.Set("command", e->GetName());
    args.Set("args", e->GetArgs());
});
