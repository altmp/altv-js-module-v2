#include "Class.h"
#include "interfaces/IResource.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedPedClass;
extern js::Class pedClass("Ped", &sharedPedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.GetByID<alt::IBaseObject::Type::PED>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::PED>();
});
