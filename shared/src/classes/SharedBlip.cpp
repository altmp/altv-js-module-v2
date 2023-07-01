#include "Class.h"
#include "cpp-sdk/ICore.h"

// clang-format off
extern js::Class baseObjectClass;
extern js::Class sharedBlipClass("SharedBlip", &baseObjectClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.Property<&alt::IBlip::IsGlobal>("global");
    tpl.Property<&alt::IBlip::IsAttached>("isAttached");
    tpl.Property<&alt::IBlip::AttachedTo>("attachedTo");
    tpl.Property<&alt::IBlip::GetBlipType, &alt::IBlip::SetBlipType>("blipType");
    tpl.Property<&alt::IBlip::GetScaleXY, &alt::IBlip::SetScaleXY>("scale");
    tpl.Property<&alt::IBlip::GetDisplay, &alt::IBlip::SetDisplay>("display");
    tpl.Property<&alt::IBlip::GetSprite, &alt::IBlip::SetSprite>("sprite");
    tpl.Property<&alt::IBlip::GetColor, &alt::IBlip::SetColor>("color");
    tpl.Property<&alt::IBlip::GetSecondaryColor, &alt::IBlip::SetSecondaryColor>("secondaryColor");
    tpl.Property<&alt::IBlip::GetAlpha, &alt::IBlip::SetAlpha>("alpha");
    tpl.Property<&alt::IBlip::GetFlashTimer, &alt::IBlip::SetFlashTimer>("flashTimer");
    tpl.Property<&alt::IBlip::GetFlashInterval, &alt::IBlip::SetFlashInterval>("flashInterval");
    tpl.Property<&alt::IBlip::GetAsFriendly, &alt::IBlip::SetAsFriendly>("friendly");
    tpl.Property<&alt::IBlip::GetRoute, &alt::IBlip::SetRoute>("route");
    tpl.Property<&alt::IBlip::GetBright, &alt::IBlip::SetBright>("bright");
    tpl.Property<&alt::IBlip::GetNumber, &alt::IBlip::SetNumber>("number");
    tpl.Property<&alt::IBlip::GetShowCone, &alt::IBlip::SetShowCone>("showCone");
    tpl.Property<&alt::IBlip::GetFlashes, &alt::IBlip::SetFlashes>("flashes");
    tpl.Property<&alt::IBlip::GetFlashesAlternate, &alt::IBlip::SetFlashesAlternate>("flashesAlternate");
    tpl.Property<&alt::IBlip::GetAsShortRange, &alt::IBlip::SetAsShortRange>("shortRange");
    tpl.Property<&alt::IBlip::GetPriority, &alt::IBlip::SetPriority>("priority");
    tpl.Property<&alt::IBlip::GetRotation, &alt::IBlip::SetRotation>("rotation");
    tpl.Property<&alt::IBlip::GetGxtName, &alt::IBlip::SetGxtName>("gxtName");
    tpl.Property<&alt::IBlip::GetName, &alt::IBlip::SetName>("name");
    tpl.Property<&alt::IBlip::GetRouteColor, &alt::IBlip::SetRouteColor>("routeColor");
    tpl.Property<&alt::IBlip::GetPulse, &alt::IBlip::SetPulse>("pulse");
    tpl.Property<&alt::IBlip::GetAsMissionCreator, &alt::IBlip::SetAsMissionCreator>("missionCreator");
    tpl.Property<&alt::IBlip::GetTickVisible, &alt::IBlip::SetTickVisible>("tickVisible");
    tpl.Property<&alt::IBlip::GetHeadingIndicatorVisible, &alt::IBlip::SetHeadingIndicatorVisible>("headingIndicatorVisible");
    tpl.Property<&alt::IBlip::GetOutlineIndicatorVisible, &alt::IBlip::SetOutlineIndicatorVisible>("outlineIndicatorVisible");
    tpl.Property<&alt::IBlip::GetFriendIndicatorVisible, &alt::IBlip::SetFriendIndicatorVisible>("friendIndicatorVisible");
    tpl.Property<&alt::IBlip::GetCrewIndicatorVisible, &alt::IBlip::SetCrewIndicatorVisible>("crewIndicatorVisible");
    tpl.Property<&alt::IBlip::GetCategory, &alt::IBlip::SetCategory>("category");
    tpl.Property<&alt::IBlip::GetAsHighDetail, &alt::IBlip::SetAsHighDetail>("highDetail");
    tpl.Property<&alt::IBlip::GetShrinked, &alt::IBlip::SetShrinked>("shrinked");
    tpl.Property<&alt::IBlip::IsVisible, &alt::IBlip::SetVisible>("visible");

    tpl.Method<&alt::IBlip::AttachTo>("attachTo");
    tpl.Method<&alt::IBlip::Fade>("fade");
});
