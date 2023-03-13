#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;
    alt::IEntity* entity = alt::ICore::Instance().GetEntityByID(id);
    if(!entity || entity->GetType() != alt::IBaseObject::Type::PLAYER) ctx.Return(nullptr);
    else
        ctx.Return((alt::IBaseObject*)entity);
}

// clang-format off
extern js::Class sharedPlayerClass;
extern js::Class playerClass("Player", &sharedPlayerClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PLAYER);

    tpl.StaticFunction("getByID", &GetByID);
});
