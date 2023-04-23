#include "Class.h"
#include "cpp-sdk/ICore.h"

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IEntity* entity = alt::ICore::Instance().GetEntityByID(id);
    if(!entity || entity->GetType() != alt::IBaseObject::Type::NETWORK_OBJECT) ctx.Return(nullptr);
    else
        ctx.Return((alt::IBaseObject*)entity);
}

// clang-format off
extern js::Class sharedNetworkObjectClass;
extern js::Class networkObjectClass("NetworkObject", &sharedNetworkObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::NETWORK_OBJECT);

    tpl.Mehtod<&alt::INetworkObject::ActivatePhysics>("activatePhysics");
    tpl.Mehtod<&alt::INetworkObject::PlaceOnGroundProperly>("placeOnGroundProperly");

    tpl.Property<&alt::INetworkObject::GetAlpha, &alt::INetworkObject::SetAlpha>("alpha");
    tpl.Property<&alt::INetworkObject::GetTextureVariation, &alt::INetworkObject::SetTextureVariation>("textureVariation");
    tpl.Property<&alt::INetworkObject::GetLodDistance, &alt::INetworkObject::SetLodDistance>("lodDistance");

    tpl.StaticFunction("getByID", &GetByID);
});
