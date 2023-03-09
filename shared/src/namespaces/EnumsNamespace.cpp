#include "Namespace.h"
#include "magic_enum/include/magic_enum.hpp"
#include "cpp-sdk/SDK.h"

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
    tpl.StaticLazyProperty("Permission", GetEnumObject<alt::Permission>);
    tpl.StaticLazyProperty("PermissionState", GetEnumObject<alt::PermissionState>);
    tpl.StaticLazyProperty("ExplosionType", GetEnumObject<alt::CExplosionEvent::ExplosionType>);
    tpl.StaticLazyProperty("KeyState", GetEnumObject<alt::KeyState>);
    tpl.StaticLazyProperty("BlipType", GetEnumObject<alt::IBlip::BlipType>);
    tpl.StaticLazyProperty("ColShapeType", GetEnumObject<alt::IColShape::ColShapeType>);
    tpl.StaticLazyProperty("VehicleModelType", GetEnumObject<alt::VehicleModelInfo::Type>);
});
