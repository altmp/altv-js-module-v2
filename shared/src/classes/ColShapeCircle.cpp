#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeCircleClass("ColShapeCircle", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapeCircle::GetRadius>("radius");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
