#include "Class.h"

static void AllWorldGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetWorldObjects());
}

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    if (auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId); obj->GetType() == alt::IBaseObject::Type::LOCAL_OBJECT)
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

static void AttachTo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(4, 7)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::BASE_OBJECT })) return;
    alt::ILocalObject* object = ctx.GetThisObject<alt::ILocalObject>();

    int16_t bone;
    if(!ctx.GetArg(1, bone)) return;

    alt::Position pos;
    if(!ctx.GetArg(2, pos)) return;

    alt::Rotation rot;
    if(!ctx.GetArg(3, rot)) return;

    bool useSoftPinning = ctx.GetArg<bool>(4, false);
    bool collision = ctx.GetArg<bool>(5, false);
    bool fixedRot = ctx.GetArg<bool>(6, false);

    if(ctx.GetArgType(0) == js::Type::NUMBER)
    {
        uint32_t scriptId;
        if(!ctx.GetArg(0, scriptId)) return;

        object->AttachToEntity(scriptId, bone, pos, rot, useSoftPinning, collision, fixedRot);
    }
    else
    {
        alt::IEntity* target;
        if(!ctx.GetArg(0, target)) return;

        object->AttachToEntity(target, bone, pos, rot, useSoftPinning, collision, fixedRot);
    }
}

// clang-format off
extern js::Class objectClass;
extern js::Class localObjectClass("LocalObject", &objectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::LOCAL_OBJECT);

    tpl.Property<&alt::ILocalObject::GetModel, &alt::ILocalObject::SetModel>("model");
    tpl.Property<&alt::ILocalObject::GetAlpha, &alt::ILocalObject::SetAlpha>("alpha");
    tpl.Property<&alt::ILocalObject::IsDynamic>("isDynamic");
    tpl.Property<&alt::ILocalObject::GetLodDistance, &alt::ILocalObject::SetLodDistance>("lodDistance");
    tpl.Property<&alt::ILocalObject::HasGravity, &alt::ILocalObject::ToggleGravity>("hasGravity");
    tpl.Property<&alt::ILocalObject::IsCollisionEnabled>("isCollisionEnabled");
    tpl.Property<&alt::ILocalObject::IsPositionFrozen, &alt::ILocalObject::SetPositionFrozen>("positionFrozen");
    tpl.Property<&alt::ILocalObject::GetTextureVariation, &alt::ILocalObject::SetTextureVariation>("textureVariation");
    tpl.Property<&alt::ILocalObject::IsWorldObject>("isWorldObject");
    tpl.Property<&alt::ILocalObject::IsWeaponObject>("isWeaponObject");
    tpl.Property<&alt::ILocalObject::IsStreamedIn>("isStreamedIn");
    tpl.Property<&alt::ILocalObject::UsesStreaming>("useStreaming");
    tpl.Property<&alt::ILocalObject::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ILocalObject::GetVisible, &alt::ILocalObject::SetVisible>("visible");

    tpl.Method<&alt::ILocalObject::ResetAlpha>("resetAlpha");
    tpl.Method("attachTo", AttachTo);
    tpl.Method<&alt::ILocalObject::Detach>("detach");
    tpl.Method<&alt::ILocalObject::ToggleCollision>("toggleCollision");
    tpl.Method<&alt::ILocalObject::PlaceOnGroundProperly>("placeOnGroundProperly");
    tpl.Method<&alt::ILocalObject::ActivatePhysics>("activatePhysics");

    tpl.StaticProperty("allWorld", AllWorldGetter);

    tpl.GetByID<alt::IBaseObject::Type::LOCAL_OBJECT>();
    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
