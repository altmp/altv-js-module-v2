#include "Event.h"

// clang-format off

static void WillAnswer(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CClientScriptRPCEvent>();

    ctx.Return(ev->WillAnswer());
}

static void Answer(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(1)) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CClientScriptRPCEvent>();

    alt::MValue answer;
    if(!ctx.GetArg(0, answer)) return;

    ctx.Return(ev->Answer(answer));
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

static js::Event clientScriptRpcEvent(alt::CEvent::Type::CLIENT_SCRIPT_RPC_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CClientScriptRPCEvent*>(ev);

    args.Set("player", e->GetTarget());
    args.Set("name", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    args.Set("args", eventArgs);

    args.Set("answerID", e->GetAnswerID());

    args.SetMethod("willAnswer", WillAnswer);
    args.SetMethod("answer", Answer);
    args.SetMethod("answerWithError", AnswerWithError);
});
