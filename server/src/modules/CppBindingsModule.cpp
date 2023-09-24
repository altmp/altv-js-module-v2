#include "Module.h"

static void AnswerRPC(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(3, 4)) return;

    alt::IPlayer* target;
    if(!ctx.GetArg(0, target)) return;

    uint16_t answerID;
    if(!ctx.GetArg(1, answerID)) return;

    alt::MValue answer;
    if(!ctx.GetArg(2, answer)) return;

    std::string error = ctx.GetArg<std::string>(3);

    alt::ICore::Instance().TriggerClientRPCAnswer(target, answerID, answer, error);
}

// clang-format off
extern js::Module sharedCppBindingsModule;
// !!! Make sure to keep the name as cppBindings
extern js::Module cppBindingsModule("cppBindings", "sharedCppBindings", [](js::ModuleTemplate& module)
{
    module.StaticFunction("answerRPC", AnswerRPC);
});
