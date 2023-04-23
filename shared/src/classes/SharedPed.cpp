#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class entityClass;
extern js::Class sharedPedClass("SharedPed", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IPed::GetHealth>("health");
    tpl.Property<&alt::IPed::GetMaxHealth>("maxHealth");
    tpl.Property<&alt::IPed::GetArmour>("armour");
    tpl.Property<&alt::IPed::GetCurrentWeapon>("currentWeapon");
});
