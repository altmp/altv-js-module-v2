#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class sharedBlipClass("Blip", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.LazyProperty<alt::IBlip, &alt::IBlip::GetID>("id");

    tpl.Property<alt::IBlip, &alt::IBlip::IsGlobal>("isGlobal");
    tpl.Property<alt::IBlip, &alt::IBlip::GetTarget>("target");
    tpl.Property<alt::IBlip, &alt::IBlip::IsAttached>("isAttached");
    tpl.Property<alt::IBlip, &alt::IBlip::AttachedTo>("attachedTo");
    tpl.Property<alt::IBlip, &alt::IBlip::GetBlipType>("blipType");
    tpl.Property<alt::IBlip, alt::Vector2f, &alt::IBlip::GetScaleXY, &alt::IBlip::SetScaleXY>("scale");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetDisplay, &alt::IBlip::SetDisplay>("display");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetSprite, &alt::IBlip::SetSprite>("sprite");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetColor, &alt::IBlip::SetColor>("color");
    tpl.Property<alt::IBlip, alt::RGBA, &alt::IBlip::GetSecondaryColor, &alt::IBlip::SetSecondaryColor>("secondaryColor");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetAlpha, &alt::IBlip::SetAlpha>("alpha");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetFlashTimer, &alt::IBlip::SetFlashTimer>("flashTimer");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetFlashInterval, &alt::IBlip::SetFlashInterval>("flashInterval");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetAsFriendly, &alt::IBlip::SetAsFriendly>("friendly");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetRoute, &alt::IBlip::SetRoute>("route");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetBright, &alt::IBlip::SetBright>("bright");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetNumber, &alt::IBlip::SetNumber>("number");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetShowCone, &alt::IBlip::SetShowCone>("showCone");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetFlashes, &alt::IBlip::SetFlashes>("flashes");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetFlashesAlternate, &alt::IBlip::SetFlashesAlternate>("flashesAlternate");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetAsShortRange, &alt::IBlip::SetAsShortRange>("shortRange");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetPriority, &alt::IBlip::SetPriority>("priority");
    tpl.Property<alt::IBlip, float, &alt::IBlip::GetRotation, &alt::IBlip::SetRotation>("rotation");
    tpl.Property<alt::IBlip, std::string, const std::string&, &alt::IBlip::GetGxtName, &alt::IBlip::SetGxtName>("gxtName");
    tpl.Property<alt::IBlip, std::string, const std::string&, &alt::IBlip::GetName, &alt::IBlip::SetName>("name");
    tpl.Property<alt::IBlip, alt::RGBA, &alt::IBlip::GetRouteColor, &alt::IBlip::SetRouteColor>("routeColor");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetPulse, &alt::IBlip::SetPulse>("pulse");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetAsMissionCreator, &alt::IBlip::SetAsMissionCreator>("missionCreator");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetTickVisible, &alt::IBlip::SetTickVisible>("tickVisible");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetHeadingIndicatorVisible, &alt::IBlip::SetHeadingIndicatorVisible>("headingIndicatorVisible");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetOutlineIndicatorVisible, &alt::IBlip::SetOutlineIndicatorVisible>("outlineIndicatorVisible");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetFriendIndicatorVisible, &alt::IBlip::SetFriendIndicatorVisible>("friendIndicatorVisible");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetCrewIndicatorVisible, &alt::IBlip::SetCrewIndicatorVisible>("crewIndicatorVisible");
    tpl.Property<alt::IBlip, int, &alt::IBlip::GetCategory, &alt::IBlip::SetCategory>("category");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetAsHighDetail, &alt::IBlip::SetAsHighDetail>("highDetail");
    tpl.Property<alt::IBlip, bool, &alt::IBlip::GetShrinked, &alt::IBlip::SetShrinked>("shrinked");

    tpl.Method<alt::IBlip, void, alt::IEntity*, &alt::IBlip::AttachTo>("attachTo");
    tpl.Method<alt::IBlip, void, uint32_t, uint32_t, &alt::IBlip::Fade>("fade");
});
