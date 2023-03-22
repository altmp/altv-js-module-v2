#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class entityClass;
extern js::Class pedClass("Ped", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.Property<alt::IPed, uint16_t, &alt::IPed::GetHealth, &alt::IPed::SetHealth>("health");
    tpl.Property<alt::IPed, uint16_t, &alt::IPed::GetMaxHealth, &alt::IPed::SetMaxHealth>("maxHealth");
    tpl.Property<alt::IPed, uint16_t, &alt::IPed::GetArmour, &alt::IPed::SetArmour>("armour");
    tpl.Property<alt::IPed, uint32_t, &alt::IPed::GetCurrentWeapon, &alt::IPed::SetCurrentWeapon>("currentWeapon");
});
