#include "Class.h"

// clang-format off
extern js::Class colShapeClass;
extern js::Class checkpointClass("Checkpoint", &colShapeClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::CHECKPOINT);

    tpl.GetByID<alt::IBaseObject::Type::CHECKPOINT>();
});
