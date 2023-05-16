#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IEntity* entity = alt::ICore::Instance().GetEntityBySyncID(id);
    if(!entity || entity->GetType() != alt::IBaseObject::Type::PED) ctx.Return(nullptr);
    else
        ctx.Return((alt::IBaseObject*)entity);
}

// clang-format off
extern js::Class sharedPedClass;
extern js::Class pedClass("Ped", &sharedPedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.Property<&alt::IPed::GetHealth, &alt::IPed::SetHealth>("health");
    tpl.Property<&alt::IPed::GetMaxHealth, &alt::IPed::SetMaxHealth>("maxHealth");
    tpl.Property<&alt::IPed::GetArmour, &alt::IPed::SetArmour>("armour");
    tpl.Property<&alt::IPed::GetCurrentWeapon, &alt::IPed::SetCurrentWeapon>("currentWeapon");

    tpl.StaticFunction("getByID", &GetByID);
});
