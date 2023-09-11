#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeRectClass("ColShapeRect", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    tpl.LazyProperty<&alt::IColShapeRect::GetMin>("min");
    tpl.LazyProperty<&alt::IColShapeRect::GetMax>("max");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
