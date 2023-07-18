#include "Namespace.h"
#include "interfaces/IResource.h"

static void AddGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    std::string val;
    if(!ctx.GetArg(1, val)) return;

    ctx.GetResource()->GetResource()->AddGxtText(hash, val);
}

static void RemoveGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    ctx.GetResource()->GetResource()->RemoveGxtText(hash);
}

static void GetGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    ctx.Return(ctx.GetResource()->GetResource()->GetGxtText(hash));
}

// clang-format off
extern js::Namespace gxtNamespace("Gxt", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("add", AddGxtText);
    tpl.StaticFunction("remove", RemoveGxtText);
    tpl.StaticFunction("get", GetGxtText);
});
