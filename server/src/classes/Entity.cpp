#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;
    ctx.Return((alt::IBaseObject*)alt::ICore::Instance().GetEntityByID(id));
}

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class entityClass("Entity", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticFunction("getByID", &GetByID);
});
