#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class colShapeClass("ColShape", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<alt::IColShape, &alt::IColShape::GetColshapeType>("type");
    tpl.Property<&alt::IColShape::IsPlayersOnly, &alt::IColShape::SetPlayersOnly>("playersOnly");

    tpl.Mehtod<&alt::IColShape::IsEntityIn>("isEntityIn");
    tpl.Mehtod<&alt::IColShape::IsEntityIdIn>("isEntityIdIn");
    tpl.Mehtod<&alt::IColShape::IsPointIn>("isPointIn");
});

extern js::Class checkpointClass("Checkpoint", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);
});
