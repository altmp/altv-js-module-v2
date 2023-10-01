#include "Event.h"

static void WillAnswer(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CScriptRPCEvent>();

    ctx.Return(ev->WillAnswer());
}

static void Answer(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;
    if(!ctx.CheckArgCount(1)) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CScriptRPCEvent>();

    alt::MValue answer;
    if(!ctx.GetArg(0, answer)) return;

    ctx.Return(ev->Answer(answer));
}

static void AnswerWithError(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    if(!ctx.CheckExtraInternalFieldValue()) return;
    auto* ev = ctx.GetExtraInternalFieldValue<alt::CScriptRPCEvent>();

    std::string errorMessage;
    if(!ctx.GetArg(0, errorMessage)) return;

    ctx.Return(ev->AnswerWithError(errorMessage));
}

// clang-format off
static js::Event scriptRpcEvent(alt::CEvent::Type::SCRIPT_RPC_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CScriptRPCEvent*>(ev);

    args.Set("name", e->GetName());

    const alt::MValueArgs& eventArgs = e->GetArgs();
    args.Set("args", eventArgs);

    args.Set("answerID", e->GetAnswerID());

    args.SetMethod("willAnswer", WillAnswer);
    args.SetMethod("answer", Answer);
    args.SetMethod("answerWithError", AnswerWithError);

    #ifdef ALT_SERVER_API
    args.Set("player", e->GetTarget());
    #endif
});

static js::Event scriptRpcAnswerEvent(alt::CEvent::Type::SCRIPT_RPC_ANSWER_EVENT, [](const alt::CEvent* ev, js::Event::EventArgs& args)
{
    auto e = static_cast<const alt::CScriptRPCAnswerEvent*>(ev);

    args.Set("answerID", e->GetAnswerID());
    args.Set("answer", e->GetAnswer());
    args.Set("answerError", e->GetAnswerError());

    #ifdef ALT_SERVER_API
    args.Set("player", e->GetTarget());
    #endif
});
