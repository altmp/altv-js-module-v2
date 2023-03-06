#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass("BaseObject", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Method<alt::IBaseObject, alt::MValueConst, const std::string&, &alt::IBaseObject::GetMetaData>("getMeta");
    tpl.Method<alt::IBaseObject, void, const std::string&, alt::MValue, &alt::IBaseObject::SetMetaData>("setMeta");
    tpl.Property<alt::IBaseObject, &alt::IBaseObject::GetType>("type");
});
