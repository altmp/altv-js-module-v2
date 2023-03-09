#include "Namespace.h"
#include "magic_enum/include/magic_enum.hpp"

template<typename T>
static void GetEnumObject(js::LazyPropertyContext& ctx)
{
    js::Object obj;
    auto values = magic_enum::template enum_entries<T>();
    for(auto& [value, key] : values)
    {
        obj.Set(key.data(), (int)value);
    }
    ctx.Return(obj.Get());
}

// clang-format off
extern js::Namespace enumsNamespace("Enums", [](js::NamespaceTemplate& tpl) {
    tpl.StaticLazyProperty("BaseObjectType", GetEnumObject<alt::IBaseObject::Type>);
});
