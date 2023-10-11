#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    if (auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId))
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class entityClass("Entity", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IEntity::GetScriptID>("scriptID");

    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
