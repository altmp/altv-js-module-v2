#include "Namespace.h"
#include "Event.h"

#include "magic_enum/include/magic_enum.hpp"
#include "cpp-sdk/SDK.h"
#include "cpp-sdk/events/CKeyboardEvent.h"

// clang-format off
extern js::Namespace enumsNamespace("Enums", [](js::NamespaceTemplate& tpl) {
    tpl.StaticEnum<alt::IBaseObject::Type>("BaseObjectType");
    tpl.StaticEnum<alt::Permission>("Permission");
    tpl.StaticEnum<alt::CExplosionEvent::ExplosionType>("ExplosionType");
    tpl.StaticEnum<alt::IBlip::BlipType>("BlipType");
    tpl.StaticEnum<alt::IColShape::ColShapeType>("ColShapeType");
    tpl.StaticEnum<alt::CPlayerConnectDeniedEvent::Reason>("ConnectDeniedReason");
    tpl.StaticEnum<alt::VehicleModelInfo::Type>("VehicleModelType");
    tpl.StaticEnum<alt::CWeaponDamageEvent::BodyPart>("BodyPart");
    tpl.StaticEnum<alt::CEvent::Type, alt::CEvent::Type::NONE, alt::CEvent::Type::ALL>("EventType");
    tpl.StaticEnum<js::EventType, js::EventType::NONE, js::EventType::SIZE>("CustomEventType");
    tpl.StaticEnum<alt::Benefit>("Benefit");
    tpl.StaticEnum<alt::Metric::Type>("MetricType");
    tpl.StaticEnum<alt::AmmoSpecialType>("AmmoSpecialType");
    tpl.StaticEnum<alt::CKeyboardEvent::KeyState>("KeyState");
    tpl.StaticEnum<alt::CVoiceConnectionEvent::State>("VoiceConnectionState");
    tpl.StaticEnum<alt::IMarker::MarkerType>("MarkerType");
    tpl.StaticEnum<alt::CloudAuthResult>("CloudAuthResult");
    tpl.StaticEnum<alt::Benefit>("Benefit");
    tpl.StaticEnum<alt::ITextLabel::Alignment>("TextLabelAlignment");
});
