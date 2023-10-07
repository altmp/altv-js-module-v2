#include "Class.h"
#include "cpp-sdk/ICore.h"

static void NeonGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVehicle* vehicle = ctx.GetParent<alt::IVehicle>();

    bool left, right, front, back;
    vehicle->GetNeonActive(&left, &right, &front, &back);
    bool val = false;
    std::string prop = ctx.GetProperty();
    if(prop == "left") val = left;
    else if(prop == "right")
        val = right;
    else if(prop == "front")
        val = front;
    else if(prop == "back")
        val = back;

    ctx.Return(val);
}

static void NeonEnumerator(js::DynamicPropertyEnumeratorContext& ctx)
{
    js::Array arr(4);
    arr.Set(0, "left");
    arr.Set(1, "right");
    arr.Set(2, "front");
    arr.Set(3, "back");
    ctx.Return(arr.Get());
}

// clang-format off
extern js::Class entityClass;
extern js::Class sharedVehicleClass("SharedVehicle", &entityClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.DynamicProperty("neon", &NeonGetter, nullptr, nullptr, &NeonEnumerator);

    tpl.Property<&alt::IVehicle::GetDriver>("driver");
    tpl.Property<&alt::IVehicle::IsDestroyed>("isDestroyed");
    tpl.Property<&alt::IVehicle::GetModKitsCount>("modKitsCount");
    tpl.Property<&alt::IVehicle::GetModKit>("modKit");
    tpl.Property<&alt::IVehicle::IsPrimaryColorRGB>("isPrimaryColorRGB");
    tpl.Property<&alt::IVehicle::GetPrimaryColor>("primaryColor");
    tpl.Property<&alt::IVehicle::GetPrimaryColorRGB>("primaryColorRGB");
    tpl.Property<&alt::IVehicle::IsSecondaryColorRGB>("isSecondaryColorRGB");
    tpl.Property<&alt::IVehicle::GetSecondaryColor>("secondaryColor");
    tpl.Property<&alt::IVehicle::GetSecondaryColorRGB>("secondaryColorRGB");
    tpl.Property<&alt::IVehicle::GetPearlColor>("pearlColor");
    tpl.Property<&alt::IVehicle::GetWheelColor>("wheelColor");
    tpl.Property<&alt::IVehicle::GetInteriorColor>("interiorColor");
    tpl.Property<&alt::IVehicle::GetDashboardColor>("dashboardColor");
    tpl.Property<&alt::IVehicle::IsTireSmokeColorCustom>("isTireSmokeColorCustom");
    tpl.Property<&alt::IVehicle::GetTireSmokeColor>("tireSmokeColor");
    tpl.Property<&alt::IVehicle::GetWheelType>("wheelType");
    tpl.Property<&alt::IVehicle::GetWheelVariation>("wheelVariation");
    tpl.Property<&alt::IVehicle::GetCustomTires>("customTires");
    tpl.Property<&alt::IVehicle::GetSpecialDarkness>("specialDarkness");
    tpl.Property<&alt::IVehicle::GetNumberplateIndex>("numberplateIndex");
    tpl.Property<&alt::IVehicle::GetNumberplateText>("numberplateText");
    tpl.Property<&alt::IVehicle::GetWindowTint>("windowTint");
    tpl.Property<&alt::IVehicle::GetDirtLevel>("dirtLevel");
    tpl.Property<&alt::IVehicle::IsNeonActive>("isNeonActive");
    tpl.Property<&alt::IVehicle::GetNeonColor>("neonColor");
    tpl.Property<&alt::IVehicle::GetLivery>("livery");
    tpl.Property<&alt::IVehicle::GetRoofLivery>("roofLivery");
    tpl.Property<&alt::IVehicle::GetAppearanceDataBase64>("appearanceDataBase64");
    tpl.Property<&alt::IVehicle::IsEngineOn>("isEngineOn");
    tpl.Property<&alt::IVehicle::IsHandbrakeActive>("isHandbrakeActive");
    tpl.Property<&alt::IVehicle::GetHeadlightColor>("headlightColor");
    tpl.Property<&alt::IVehicle::GetRadioStationIndex>("radioStationIndex");
    tpl.Property<&alt::IVehicle::IsSirenActive>("isSirenActive");
    tpl.Property<&alt::IVehicle::GetLockState>("lockState");
    tpl.Property<&alt::IVehicle::IsDaylightOn>("isDaylightOn");
    tpl.Property<&alt::IVehicle::IsNightlightOn>("isNightlightOn");
    tpl.Property<&alt::IVehicle::GetRoofState>("roofState");
    tpl.Property<&alt::IVehicle::IsFlamethrowerActive>("isFlamethrowerActive");
    tpl.Property<&alt::IVehicle::GetLightsMultiplier>("lightsMultiplier");
    tpl.Property<&alt::IVehicle::GetGameStateBase64>("gameStateBase64");
    tpl.Property<&alt::IVehicle::GetEngineHealth>("engineHealth");
    tpl.Property<&alt::IVehicle::GetPetrolTankHealth>("petrolTankHealth");
    tpl.Property<&alt::IVehicle::GetWheelsCount>("wheelsCount");
    tpl.Property<&alt::IVehicle::GetRepairsCount>("repairsCount");
    tpl.Property<&alt::IVehicle::GetBodyHealth>("bodyHealth");
    tpl.Property<&alt::IVehicle::GetBodyAdditionalHealth>("bodyAdditionalHealth");
    tpl.Property<&alt::IVehicle::HasArmoredWindows>("hasArmoredWindows");
    tpl.Property<&alt::IVehicle::GetDamageDataBase64>("damageDataBase64");
    tpl.Property<&alt::IVehicle::IsManualEngineControl>("isManualEngineControl");
    tpl.Property<&alt::IVehicle::GetScriptDataBase64>("scriptDataBase64");
    tpl.Property<&alt::IVehicle::GetVelocity>("velocity");
    tpl.Property<&alt::IVehicle::GetSteeringAngle>("steeringAngle");
    tpl.Property<&alt::IVehicle::GetRearWheelVariation>("rearWheelVariation");

    tpl.Method<&alt::IVehicle::GetMod>("getMod");
    tpl.Method<&alt::IVehicle::GetModsCount>("getModsCount");
    tpl.Method<&alt::IVehicle::IsExtraOn>("isExtraOn");
    tpl.Method<&alt::IVehicle::GetDoorState>("getDoorState");
    tpl.Method<&alt::IVehicle::IsWindowOpened>("isWindowOpened");
    tpl.Method<&alt::IVehicle::IsWheelBurst>("isWheelBurst");
    tpl.Method<&alt::IVehicle::DoesWheelHasTire>("getWheelHasTire");
    tpl.Method<&alt::IVehicle::IsWheelDetached>("isWheelDetached");
    tpl.Method<&alt::IVehicle::IsWheelOnFire>("isWheelOnFire");
    tpl.Method<&alt::IVehicle::GetWheelHealth>("getWheelHealth");
    tpl.Method<&alt::IVehicle::GetPartDamageLevel>("getPartDamageLevel");
    tpl.Method<&alt::IVehicle::GetPartBulletHoles>("getPartBulletHoles");
    tpl.Method<&alt::IVehicle::IsLightDamaged>("isLightDamaged");
    tpl.Method<&alt::IVehicle::IsWindowDamaged>("isWindowDamaged");
    tpl.Method<&alt::IVehicle::IsSpecialLightDamaged>("isSpecialLightDamaged");
    tpl.Method<&alt::IVehicle::GetArmoredWindowHealth>("getArmoredWindowHealth");
    tpl.Method<&alt::IVehicle::GetArmoredWindowShootCount>("getArmoredWindowShootCount");
    tpl.Method<&alt::IVehicle::GetBumperDamageLevel>("getBumperDamageLevel");
    tpl.Method<&alt::IVehicle::ToggleExtra>("toggleExtra");
});
