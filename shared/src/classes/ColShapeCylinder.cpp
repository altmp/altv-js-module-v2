#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class colShapeCylinderClass("ColShapeCylinder", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::COLSHAPE);

    // TODO (xLuxy): wait for new build (https://github.com/altmp/cpp-sdk/commit/ab604174853306108976057a6c1e9c5f0b54c27c)
    // tpl.LazyProperty<&alt::IColShapeCylinder::GetRadius>("radius");
    // tpl.LazyProperty<&alt::IColShapeCylinder::GetHeight>("radius");

    tpl.GetByID<alt::IBaseObject::Type::COLSHAPE>();
});
