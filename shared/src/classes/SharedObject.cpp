#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class entityClass;
extern js::Class sharedObjectClass("SharedObject", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IObject::GetAlpha>("alpha");
    tpl.Property<&alt::IObject::GetTextureVariation>("textureVariation");
    tpl.Property<&alt::IObject::GetLodDistance>("lodDistance");
});
