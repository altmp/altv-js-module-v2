#include "Class.h"

// clang-format off
extern js::Class objectClass;
extern js::Class weaponObjectClass("WeaponObject", &objectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::OBJECT);

    tpl.Property<&alt::IObject::GetTintIndex, &alt::IObject::SetTintIndex>("tintIndex");

    tpl.Method<&alt::IObject::GetComponentTintIndex>("getComponentTintIndex");
    tpl.Method<&alt::IObject::SetComponentTintIndex>("setComponentTintIndex");
    tpl.Method<&alt::IObject::GiveComponent>("giveComponent");
    tpl.Method<&alt::IObject::RemoveComponent>("removeComponent");

    tpl.GetByID<alt::IBaseObject::Type::OBJECT>();
});
