#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class sharedEntityClass("Entity", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<alt::IEntity, &alt::IEntity::GetID>("id");
});
