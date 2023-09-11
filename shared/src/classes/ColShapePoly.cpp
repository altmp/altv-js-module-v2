#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapePolyClass("ColShapePoly", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapePoly::GetMinZ>("minZ");
    tpl.LazyProperty<&alt::IColShapePoly::GetMaxZ>("maxZ");
    tpl.LazyProperty<&alt::IColShapePoly::GetPoints>("points");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
