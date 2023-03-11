#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedWorldObjectClass;
extern js::Class sharedEntityClass("Entity", &sharedWorldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<alt::IEntity, &alt::IEntity::GetID>("id");
});
