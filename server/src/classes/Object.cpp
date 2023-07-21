#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedObjectClass;
extern js::Class objectClass("Object", &sharedObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::OBJECT);

    tpl.Method<&alt::IObject::ActivatePhysics>("activatePhysics");
    tpl.Method<&alt::IObject::PlaceOnGroundProperly>("placeOnGroundProperly");

    tpl.Property<&alt::IObject::GetAlpha, &alt::IObject::SetAlpha>("alpha");
    tpl.Property<&alt::IObject::GetTextureVariation, &alt::IObject::SetTextureVariation>("textureVariation");
    tpl.Property<&alt::IObject::GetLodDistance, &alt::IObject::SetLodDistance>("lodDistance");

    tpl.GetByID<alt::IBaseObject::Type::OBJECT>();
});
