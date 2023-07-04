#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class colShapeClass("ColShape", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShape::GetColshapeType>("colShapeType");
    tpl.Property<&alt::IColShape::IsPlayersOnly, &alt::IColShape::SetPlayersOnly>("playersOnly");

    tpl.Method<&alt::IColShape::IsEntityIn>("isEntityIn");
    tpl.Method<&alt::IColShape::IsEntityIdIn>("isEntityIdIn");
    tpl.Method<&alt::IColShape::IsPointIn>("isPointIn");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
