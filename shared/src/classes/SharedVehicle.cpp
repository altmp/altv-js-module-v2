#include "Class.h"
#include "cpp-sdk/ICore.h"

static void NeonGetter(js::DynamicPropertyContext<v8::Value>& ctx)
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

static void NeonSetter(js::DynamicPropertyContext<v8::Value>& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVehicle* vehicle = ctx.GetParent<alt::IVehicle>();

    bool left, right, front, back;
    vehicle->GetNeonActive(&left, &right, &front, &back);
    bool val = false;
    std::string prop = ctx.GetProperty();
    if(prop == "left") left = val;
    else if(prop == "right")
        right = val;
    else if(prop == "front")
        front = val;
    else if(prop == "back")
        back = val;

    vehicle->SetNeonActive(left, right, front, back);
}

static void NeonEnumerator(js::DynamicPropertyContext<v8::Array>& ctx)
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
    tpl.DynamicProperty("neon", &NeonGetter, &NeonSetter, nullptr, &NeonEnumerator);

    tpl.Property<alt::IVehicle, &alt::IVehicle::GetDriver>("driver");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsDestroyed>("isDestroyed");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetModKitsCount>("modKitsCount");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetModKit>("modKit");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsPrimaryColorRGB>("isPrimaryColorRGB");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetPrimaryColor>("primaryColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetPrimaryColorRGB>("primaryColorRGB");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsSecondaryColorRGB>("isSecondaryColorRGB");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetSecondaryColor>("secondaryColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetSecondaryColorRGB>("secondaryColorRGB");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetPearlColor>("pearlColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetWheelColor>("wheelColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetInteriorColor>("interiorColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetDashboardColor>("dashboardColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsTireSmokeColorCustom>("isTireSmokeColorCustom");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetTireSmokeColor>("tireSmokeColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetWheelType>("wheelType");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetWheelVariation>("wheelVariation");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetCustomTires>("customTires");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetSpecialDarkness>("specialDarkness");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetNumberplateIndex>("numberPlateIndex");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetNumberplateText>("numberPlateText");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetWindowTint>("windowTint");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetDirtLevel>("dirtLevel");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsNeonActive>("isNeonActive");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetNeonColor>("neonColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetLivery>("livery");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetRoofLivery>("roofLivery");
    // todo: fix const in sdk
    //tpl.Property<alt::IVehicle, &alt::IVehicle::GetAppearanceDataBase64>("appearanceDataBase64");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsEngineOn>("isEngineOn");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsHandbrakeActive>("isHandbrakeActive");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetHeadlightColor>("headlightColor");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetRadioStationIndex>("radioStationIndex");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsSirenActive>("isSirenActive");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetLockState>("lockState");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsDaylightOn>("isDaylightOn");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsNightlightOn>("isNightlightOn");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetRoofState>("roofState");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsFlamethrowerActive>("isFlamethrowerActive");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetLightsMultiplier>("lightsMultiplier");
    // todo: fix const in sdk
    //tpl.Property<alt::IVehicle, &alt::IVehicle::GetGameStateBase64>("gameStateBase64");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetEngineHealth>("engineHealth");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetPetrolTankHealth>("petrolTankHealth");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetWheelsCount>("wheelsCount");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetRepairsCount>("repairsCount");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetBodyHealth>("bodyHealth");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetBodyAdditionalHealth>("bodyAdditionalHealth");
    tpl.Property<alt::IVehicle, &alt::IVehicle::HasArmoredWindows>("hasArmoredWindows");
    // todo: fix const in sdk
    //tpl.Property<alt::IVehicle, &alt::IVehicle::GetDamageDataBase64>("damageDataBase64");
    tpl.Property<alt::IVehicle, &alt::IVehicle::IsManualEngineControl>("isManualEngineControl");
    // todo: fix const in sdk
    //tpl.Property<alt::IVehicle, &alt::IVehicle::GetScriptDataBase64>("scriptDataBase64");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetVelocity>("velocity");

    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetMod>("getMod");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetModsCount>("getModsCount");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsExtraOn>("getIsExtraOn");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetDoorState>("getDoorState");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsWindowOpened>("getIsWindowOpened");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsWheelBurst>("getIsWheelBurst");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::DoesWheelHasTire>("getWheelHasTire");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsWheelDetached>("getIsWheelDetached");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsWheelOnFire>("getIsWheelOnFire");
    tpl.Method<alt::IVehicle, float, uint8_t, &alt::IVehicle::GetWheelHealth>("getWheelHealth");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetPartDamageLevel>("getPartDamageLevel");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetPartBulletHoles>("getPartBulletHoles");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsLightDamaged>("getIsLightDamaged");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsWindowDamaged>("getIsWindowDamaged");
    tpl.Method<alt::IVehicle, bool, uint8_t, &alt::IVehicle::IsSpecialLightDamaged>("getIsSpecialLightDamaged");
    tpl.Method<alt::IVehicle, float, uint8_t, &alt::IVehicle::GetArmoredWindowHealth>("getArmoredWindowHealth");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetArmoredWindowShootCount>("getArmoredWindowShootCount");
    tpl.Method<alt::IVehicle, uint8_t, uint8_t, &alt::IVehicle::GetBumperDamageLevel>("getBumperDamageLevel");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::ToggleExtra>("toggleExtra");
});
