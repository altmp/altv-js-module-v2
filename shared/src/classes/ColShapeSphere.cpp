#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeSphereClass("ColShapeSphere", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapeSphere::GetRadius>("radius");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
