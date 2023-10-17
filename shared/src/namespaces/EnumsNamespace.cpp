#include "Namespace.h"
#include "Event.h"

#include "magic_enum/include/magic_enum.hpp"
#include "cpp-sdk/SDK.h"
#include "cpp-sdk/events/CKeyboardEvent.h"

template<typename T>
static void GetEnumObject(js::LazyPropertyContext& ctx)
{
    js::Object obj;
    auto values = magic_enum::template enum_entries<T>();
    for(auto& [value, key] : values)
    {
        obj.Set(key.data(), (int)value);
    }
    ctx.Return(obj);
}

template<typename T, T Start, T End>
static void GetEnumObjectWithStartEnd(js::LazyPropertyContext& ctx)
{
    js::Object obj;
    auto values = magic_enum::template enum_entries<T>();
    for(int i = (int)Start + 1; i < (int)End; i++)
    {
        auto& entry = values[i];
        obj.Set(entry.second.data(), (int)entry.first);
    }
    ctx.Return(obj);
}

// clang-format off
extern js::Namespace enumsNamespace("Enums", [](js::NamespaceTemplate& tpl) {
    tpl.StaticLazyProperty("BaseObjectType", GetEnumObject<alt::IBaseObject::Type>);
    tpl.StaticLazyProperty("Permission", GetEnumObject<alt::Permission>);
    tpl.StaticLazyProperty("ExplosionType", GetEnumObject<alt::CExplosionEvent::ExplosionType>);
    tpl.StaticLazyProperty("BlipType", GetEnumObject<alt::IBlip::BlipType>);
    tpl.StaticLazyProperty("ColShapeType", GetEnumObject<alt::IColShape::ColShapeType>);
    tpl.StaticLazyProperty("ConnectDeniedReason", GetEnumObject<alt::CPlayerConnectDeniedEvent::Reason>);
    tpl.StaticLazyProperty("VehicleModelType", GetEnumObject<alt::VehicleModelInfo::Type>);
    tpl.StaticLazyProperty("BodyPart", GetEnumObject<alt::CWeaponDamageEvent::BodyPart>);
    tpl.StaticLazyProperty("EventType", GetEnumObjectWithStartEnd<alt::CEvent::Type, alt::CEvent::Type::NONE, alt::CEvent::Type::ALL>);
    tpl.StaticLazyProperty("CustomEventType", GetEnumObjectWithStartEnd<js::EventType, js::EventType::NONE, js::EventType::SIZE>);
    tpl.StaticLazyProperty("MetricType", GetEnumObject<alt::Metric::Type>);
    tpl.StaticLazyProperty("AmmoSpecialType", GetEnumObject<alt::AmmoSpecialType>);
    tpl.StaticLazyProperty("KeyState", GetEnumObject<alt::CKeyboardEvent::KeyState>);
    tpl.StaticLazyProperty("VoiceConnectionState", GetEnumObject<alt::CVoiceConnectionEvent::State>);
    tpl.StaticLazyProperty("MarkerType", GetEnumObject<alt::IMarker::MarkerType>);
    tpl.StaticLazyProperty("CloudAuthResult", GetEnumObject<alt::CloudAuthResult>);
});
