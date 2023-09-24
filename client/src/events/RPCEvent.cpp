#include "Event.h"
#include "events/CAudioEvent.h"

// clang-format off
static js::Event serverScriptRpcEvent(alt::CEvent::Type::SERVER_SCRIPT_RPC_ANSWER_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CServerScriptRPCAnswerEvent*>(ev);

    args.Set("answerID", e->GetAnswerID());

    const alt::MValueArgs& answerArgs = e->GetAnswer();
    args.Set("answer", answerArgs);

    args.Set("answerError", e->GetAnswerError());
});
