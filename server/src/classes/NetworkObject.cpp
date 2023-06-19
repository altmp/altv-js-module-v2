#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedNetworkObjectClass;
extern js::Class networkObjectClass("NetworkObject", &sharedNetworkObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::NETWORK_OBJECT);

    tpl.Method<&alt::INetworkObject::ActivatePhysics>("activatePhysics");
    tpl.Method<&alt::INetworkObject::PlaceOnGroundProperly>("placeOnGroundProperly");

    tpl.Property<&alt::INetworkObject::GetAlpha, &alt::INetworkObject::SetAlpha>("alpha");
    tpl.Property<&alt::INetworkObject::GetTextureVariation, &alt::INetworkObject::SetTextureVariation>("textureVariation");
    tpl.Property<&alt::INetworkObject::GetLodDistance, &alt::INetworkObject::SetLodDistance>("lodDistance");

    tpl.GetByID<alt::IBaseObject::Type::NETWORK_OBJECT>();
});
