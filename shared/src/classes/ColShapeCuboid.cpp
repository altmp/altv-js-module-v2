#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeCuboidClass("ColShapeCuboid", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapeCuboid::GetMax>("max");
    tpl.LazyProperty<&alt::IColShapeCuboid::GetMin>("min");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
