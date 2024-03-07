#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedVirtualEntityGroupClass;
extern js::Class virtualEntityGroupClass("VirtualEntityGroup", &sharedVirtualEntityGroupClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP);

    tpl.GetByID<alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP>();
});
