#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class worldObjectClass;
extern js::Class colShapeClass("ColShape", &worldObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<alt::IColShape, &alt::IColShape::GetColshapeType>("type");
    tpl.Property<alt::IColShape, bool, &alt::IColShape::IsPlayersOnly, &alt::IColShape::SetPlayersOnly>("playersOnly");

    tpl.Method<alt::IColShape, bool, alt::IEntity*, &alt::IColShape::IsEntityIn>("isEntityIn");
    tpl.Method<alt::IColShape, bool, uint16_t, &alt::IColShape::IsEntityIdIn>("isEntityIdIn");
    tpl.Method<alt::IColShape, bool, alt::Position, &alt::IColShape::IsPointIn>("isPointIn");
});

extern js::Class checkpointClass("Checkpoint", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{});
