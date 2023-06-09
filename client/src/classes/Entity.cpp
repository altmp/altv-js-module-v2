#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedEntityClass;
extern js::Class entityClass("Entity", &sharedEntityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IEntity::GetScriptID>("scriptID");
});
