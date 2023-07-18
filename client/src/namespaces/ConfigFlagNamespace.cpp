#include "Namespace.h"

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    ctx.Return(alt::ICore::Instance().GetConfigFlag(flag));
}

static void Set(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    bool state;
    if(!ctx.GetArg(1, state)) return;

    ctx.Return(alt::ICore::Instance().SetConfigFlag(flag, state));
}

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    ctx.Return(alt::ICore::Instance().DoesConfigFlagExist(flag));
}

// clang-format off
extern js::Namespace configFlagNamespace("ConfigFlag", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("set", Set);
    tpl.StaticFunction("exists", Exists);
});
