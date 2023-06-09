#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByID(alt::IBaseObject::Type::NETWORK_OBJECT, id);
    ctx.Return(entity);
}

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

    tpl.StaticFunction("getByID", &GetByID);
});
