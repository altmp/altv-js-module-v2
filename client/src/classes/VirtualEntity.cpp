#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedVirtualEntityClass;
extern js::Class virtualEntityClass("VirtualEntity", &sharedVirtualEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VIRTUAL_ENTITY);

    tpl.Property<&alt::IVirtualEntity::IsStreamedIn>("streamedIn");

    tpl.GetByID<alt::IBaseObject::Type::VIRTUAL_ENTITY>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::VIRTUAL_ENTITY>();
});
