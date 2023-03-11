#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedWorldObjectClass;
extern js::Class worldObjectClass("WorldObject", &sharedWorldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<alt::IWorldObject, int32_t, &alt::IWorldObject::GetDimension, &alt::IWorldObject::SetDimension>("dimension");
    tpl.Property<alt::IWorldObject, alt::Position, &alt::IWorldObject::GetPosition, &alt::IWorldObject::SetPosition>("pos");
});
