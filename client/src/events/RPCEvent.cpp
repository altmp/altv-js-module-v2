#include "Event.h"
#include "events/CAudioEvent.h"

// clang-format off
static js::Event scriptRpcEvent(alt::CEvent::Type::SCRIPT_RPC_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CScriptRPCAnswerEvent*>(ev);

    args.Set("answerID", e->GetAnswerID());
    args.Set("answer", e->GetAnswer());
    args.Set("answerError", e->GetAnswerError());
});
