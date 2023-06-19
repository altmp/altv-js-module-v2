#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedPedClass;
extern js::Class pedClass("Ped", &sharedPedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.Property<&alt::IPed::GetHealth, &alt::IPed::SetHealth>("health");
    tpl.Property<&alt::IPed::GetMaxHealth, &alt::IPed::SetMaxHealth>("maxHealth");
    tpl.Property<&alt::IPed::GetArmour, &alt::IPed::SetArmour>("armour");
    tpl.Property<&alt::IPed::GetCurrentWeapon, &alt::IPed::SetCurrentWeapon>("currentWeapon");

    tpl.GetByID<alt::IBaseObject::Type::PED>();
});
