#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class entityClass;
extern js::Class sharedNetworkObjectClass("SharedNetworkObject", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<alt::INetworkObject, &alt::INetworkObject::GetAlpha>("alpha");
    tpl.Property<alt::INetworkObject, &alt::INetworkObject::GetTextureVariation>("textureVariation");
    tpl.Property<alt::INetworkObject, &alt::INetworkObject::GetLodDistance>("lodDistance");
});
