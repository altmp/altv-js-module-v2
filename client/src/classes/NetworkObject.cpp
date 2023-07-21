#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class sharedObjectClass;
extern js::Class objectClass("Object", &sharedObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::OBJECT);

    tpl.GetByID<alt::IBaseObject::Type::OBJECT>();
});
