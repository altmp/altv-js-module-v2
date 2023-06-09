#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByID(alt::IBaseObject::Type::PED, id);
    ctx.Return(entity);
}

// clang-format off
extern js::Class sharedPedClass;
extern js::Class pedClass("Ped", &sharedPedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.StaticFunction("getByID", &GetByID);
});
