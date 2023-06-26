#include "Namespace.h"
#include "interfaces/IResource.h"

static void Get(js::FunctionContext& ctx)
{
    alt::ILocalStorage* storage = ctx.GetResource()->GetResource()->GetLocalStorage();

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    ctx.Return(storage->Get(key));
}

static void Set(js::FunctionContext& ctx)
{
    alt::ILocalStorage* storage = ctx.GetResource()->GetResource()->GetLocalStorage();

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    alt::MValue value;
    if(!ctx.GetArg(1, value)) return;

    storage->Set(key, value);
}

static void Delete(js::FunctionContext& ctx)
{
    alt::ILocalStorage* storage = ctx.GetResource()->GetResource()->GetLocalStorage();

    std::string key;
    if(!ctx.GetArg(0, key)) return;

    storage->Delete(key);
}

static void Clear(js::FunctionContext& ctx)
{
    alt::ILocalStorage* storage = ctx.GetResource()->GetResource()->GetLocalStorage();

    storage->Clear();
}

static void Save(js::FunctionContext& ctx)
{
    alt::ILocalStorage* storage = ctx.GetResource()->GetResource()->GetLocalStorage();

    ctx.Return(storage->Save());
}

// clang-format off
extern js::Namespace localStorageNamespace("LocalStorage", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("set", Set);
    tpl.StaticFunction("delete", Delete);
    tpl.StaticFunction("clear", Clear);
    tpl.StaticFunction("save", Save);
});
