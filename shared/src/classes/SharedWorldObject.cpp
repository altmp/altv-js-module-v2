#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class sharedWorldObjectClass("SharedWorldObject", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<alt::IWorldObject, &alt::IWorldObject::GetPosition>("pos");
});
