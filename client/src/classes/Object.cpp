#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    if (auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId); obj->GetType() == alt::IBaseObject::Type::OBJECT)
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
