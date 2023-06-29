#include "Class.h"

static void AllWorldGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetWorldObjects());
}

static void AttachTo(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(4)) return;
    if(!ctx.CheckArgType(0, { js::Type::NUMBER, js::Type::BASE_OBJECT })) return;
    alt::IObject* object = ctx.GetThisObject<alt::IObject>();

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
extern js::Class entityClass;
extern js::Class objectClass("Object", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::OBJECT);

    tpl.Property<&alt::IObject::GetModel, &alt::IObject::SetModel>("model");
    tpl.Property<&alt::IObject::GetAlpha, &alt::IObject::SetAlpha>("alpha");
    tpl.Property<&alt::IObject::IsDynamic>("isDynamic");
    tpl.Property<&alt::IObject::GetLodDistance, &alt::IObject::SetLodDistance>("lodDistance");
    tpl.Property<&alt::IObject::IsDynamic, &alt::IObject::ToggleGravity>("hasGravity");
    tpl.Property<&alt::IObject::IsCollisionEnabled>("isCollisionEnabled");
    tpl.Property<&alt::IObject::IsPositionFrozen, &alt::IObject::SetPositionFrozen>("positionFrozen");
    tpl.Property<&alt::IObject::GetTextureVariation, &alt::IObject::SetTextureVariation>("textureVariation");
    tpl.Property<&alt::IObject::IsWorldObject>("isWorldObject");
    tpl.Property<&alt::IObject::IsWeaponObject>("isWeaponObject");
    tpl.Property<&alt::IObject::UsesStreaming>("useStreaming");
    tpl.Property<&alt::IObject::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::IObject::GetVisible, &alt::IObject::SetVisible>("visible");

    tpl.StaticLazyProperty("allWorld", AllWorldGetter);

    tpl.Method<&alt::IObject::ResetAlpha>("resetAlpha");
    tpl.Method("attachTo", AttachTo);
    tpl.Method<&alt::IObject::Detach>("detach");
    tpl.Method<&alt::IObject::ToggleCollision>("toggleCollision");
    tpl.Method<&alt::IObject::PlaceOnGroundProperly>("placeOnGroundProperly");
    tpl.Method<&alt::IObject::ActivatePhysics>("activatePhysics");
    tpl.Method<&alt::IObject::ActivatePhysics>("activatePhysics");
});
