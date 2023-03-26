#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedNetworkObjectClass;
extern js::Class networkObjectClass("NetworkObject", &sharedNetworkObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::NETWORK_OBJECT);

    tpl.Method<alt::INetworkObject, void, alt::INetworkObject::ActivatePhysics>("activatePhysics");
    tpl.Method<alt::INetworkObject, void, alt::INetworkObject::PlaceOnGroundProperly>("placeOnGroundProperly");

    tpl.Property<alt::INetworkObject, uint8_t, &alt::INetworkObject::GetAlpha, &alt::INetworkObject::SetAlpha>("alpha");
    tpl.Property<alt::INetworkObject, uint8_t, &alt::INetworkObject::GetTextureVariation, &alt::INetworkObject::SetTextureVariation>("textureVariation");
    tpl.Property<alt::INetworkObject, uint16_t, &alt::INetworkObject::GetLodDistance, &alt::INetworkObject::SetLodDistance>("lodDistance");
});
