#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId);
    if (obj &&  (obj->GetType() == alt::IBaseObject::Type::OBJECT || obj->GetType() == alt::IBaseObject::Type::LOCAL_OBJECT))
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class sharedObjectClass;
extern js::Class objectClass("Object", &sharedObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::OBJECT);

    tpl.GetByID<alt::IBaseObject::Type::OBJECT>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::OBJECT>();

    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
