#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeCylinderClass("ColShapeCylinder", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapeCylinder::GetRadius>("radius");
    tpl.LazyProperty<&alt::IColShapeCylinder::GetHeight>("radius");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
