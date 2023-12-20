#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId);
    if (obj && (obj->GetType() == alt::IBaseObject::Type::PED || obj->GetType() == alt::IBaseObject::Type::LOCAL_PED))
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class sharedPedClass;
extern js::Class pedClass("Ped", &sharedPedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.GetByID<alt::IBaseObject::Type::PED>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::PED>();
    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
