#include "Event.h"

static void Answer(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CClientScriptRPCEvent>();

    alt::MValueArgs args;
    for(int i = 1; i < ctx.GetArgCount(); i++)
    {
        alt::MValue val;
        if(!ctx.GetArg(i, val)) continue;
        args.push_back(val);
    }

    ctx.Return(ev->Answer(args));
}

static void AnswerWithError(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckExtraInternalFieldValue()) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CClientScriptRPCEvent>();

    std::string errorMessage;
    if (!ctx.GetArg(0, errorMessage)) return;

    ctx.Return(ev->AnswerWithError(errorMessage));
}

// clang-format off
static js::Event clientRpcEvent(alt::CEvent::Type::CLIENT_SCRIPT_RPC_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientScriptRPCEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("name", e->GetName());
    args.Set("answerID", e->GetAnswerID());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    args.Set("args", eventArgs);

    args.SetMethod("answer", Answer);
    args.SetMethod("answerWithError", AnswerWithError);
});
