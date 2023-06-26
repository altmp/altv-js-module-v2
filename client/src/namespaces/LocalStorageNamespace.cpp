#include "Namespace.h"

static void StaticGet(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    js::IResource* resource = ctx.GetResource();

    ctx.Return(resource->GetLocalStorage()->Get(key));
}

static void StaticSet(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 2)) return;

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    alt::MValue val;
    if(!ctx.GetArg(1, val)) return;

    js::IResource* resource = ctx.GetResource();

    resource->GetLocalStorage()->Get(key);
}

static void StaticDelete(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    js::IResource* resource = ctx.GetResource();

    resource->GetLocalStorage()->Delete(key);
}

static void StaticClear(js::FunctionContext& ctx)
{
    js::IResource* resource = ctx.GetResource();

    resource->GetLocalStorage()->Clear();
}

static void StaticSave(js::FunctionContext& ctx)
{
    js::IResource* resource = ctx.GetResource();

    ctx.Check(resource->GetLocalStorage()->Clear(), "exceeded max local storage size (4MB)");
}

// clang-format off
extern js::Namespace localStorageNamespace("LocalStorage", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", StaticGet);
    tpl.StaticFunction("set", StaticSet);
    tpl.StaticFunction("delete", StaticDelete);
    tpl.StaticFunction("deleteAll", StaticClear);
    tpl.StaticFunction("clear", StaticClear);
    tpl.StaticFunction("save", StaticSave);
});
