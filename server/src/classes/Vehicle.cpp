#include "Class.h"
#include "cpp-sdk/ICore.h"

static void NeonSetter(js::DynamicPropertySetterContext& ctx)
{
    if(!ctx.CheckParent()) return;
    alt::IVehicle* vehicle = ctx.GetParent<alt::IVehicle>();

    bool val;
    if(!ctx.GetValue(val)) return;

    bool left, right, front, back;
    vehicle->GetNeonActive(&left, &right, &front, &back);
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

static void ModKitGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    ctx.Return(vehicle->GetModKit());
}

static void ModKitSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint8_t modKit;
    if(!ctx.GetValue(modKit)) return;

    vehicle->SetModKit(modKit);
}

static void SetMod(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint8_t category;
    if(!ctx.GetArg(0, category)) return;

    uint8_t id;
    if(!ctx.GetArg(1, id)) return;

    ctx.Check(vehicle->SetMod(category, id), "Failed to set mod, invalid mod or modkit not set");
}

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;

    alt::IBaseObject* entity = alt::ICore::Instance().GetBaseObjectByID(alt::IBaseObject::Type::VEHICLE, id);
    ctx.Return(entity);
}

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.DynamicProperty("neon", nullptr, &NeonSetter, nullptr, nullptr);

    tpl.Property("modKit", &ModKitGetter, &ModKitSetter);
    tpl.Property<&alt::IVehicle::GetPrimaryColor, &alt::IVehicle::SetPrimaryColor>("primaryColor");
    tpl.Property<&alt::IVehicle::GetPrimaryColorRGB, &alt::IVehicle::SetPrimaryColorRGB>("customPrimaryColor");
    tpl.Property<&alt::IVehicle::GetSecondaryColor, &alt::IVehicle::SetSecondaryColor>("secondaryColor");
    tpl.Property<&alt::IVehicle::GetSecondaryColorRGB, &alt::IVehicle::SetSecondaryColorRGB>("customSecondaryColor");
    tpl.Property<&alt::IVehicle::GetPearlColor, &alt::IVehicle::SetPearlColor>("pearlColor");
    tpl.Property<&alt::IVehicle::GetWheelColor, &alt::IVehicle::SetWheelColor>("wheelColor");
    tpl.Property<&alt::IVehicle::GetInteriorColor, &alt::IVehicle::SetInteriorColor>("interiorColor");
    tpl.Property<&alt::IVehicle::GetDashboardColor, &alt::IVehicle::SetDashboardColor>("dashboardColor");
    tpl.Property<&alt::IVehicle::GetTireSmokeColor, &alt::IVehicle::SetTireSmokeColor>("tireSmokeColor");
    tpl.Property<&alt::IVehicle::GetCustomTires, &alt::IVehicle::SetCustomTires>("customTires");
    tpl.Property<&alt::IVehicle::GetSpecialDarkness, &alt::IVehicle::SetSpecialDarkness>("specialDarkness");
    tpl.Property<&alt::IVehicle::GetNumberplateIndex, &alt::IVehicle::SetNumberplateIndex>("numberplateIndex");
    tpl.Property<&alt::IVehicle::GetNumberplateText, &alt::IVehicle::SetNumberplateText>("numberplateText");
    tpl.Property<&alt::IVehicle::GetWindowTint, &alt::IVehicle::SetWindowTint>("windowTint");
    tpl.Property<&alt::IVehicle::GetDirtLevel, &alt::IVehicle::SetDirtLevel>("dirtLevel");
    tpl.Property<&alt::IVehicle::GetNeonColor, &alt::IVehicle::SetNeonColor>("neonColor");
    tpl.Property<&alt::IVehicle::GetLivery, &alt::IVehicle::SetLivery>("livery");
    tpl.Property<&alt::IVehicle::GetRoofLivery, &alt::IVehicle::SetRoofLivery>("roofLivery");
    tpl.Property<&alt::IVehicle::GetAppearanceDataBase64, &alt::IVehicle::LoadAppearanceDataFromBase64>("appearanceDataBase64");
    tpl.Property<&alt::IVehicle::IsEngineOn, &alt::IVehicle::SetEngineOn>("engineOn");
    tpl.Property<&alt::IVehicle::GetHeadlightColor, &alt::IVehicle::SetHeadlightColor>("headlightColor");
    tpl.Property<&alt::IVehicle::GetRadioStationIndex, &alt::IVehicle::SetRadioStationIndex>("radioStationIndex");
    tpl.Property<&alt::IVehicle::IsSirenActive, &alt::IVehicle::SetSirenActive>("sirenActive");
    tpl.Property<&alt::IVehicle::GetLockState, &alt::IVehicle::SetLockState>("lockState");
    tpl.Property<&alt::IVehicle::GetRoofState, &alt::IVehicle::SetRoofState>("roofState");
    tpl.Property<&alt::IVehicle::GetLightsMultiplier, &alt::IVehicle::SetLightsMultiplier>("lightsMultiplier");
    tpl.Property<&alt::IVehicle::GetEngineHealth, &alt::IVehicle::SetEngineHealth>("engineHealth");
    tpl.Property<&alt::IVehicle::GetPetrolTankHealth, &alt::IVehicle::SetPetrolTankHealth>("petrolTankHealth");
    tpl.Property<&alt::IVehicle::GetBodyHealth, &alt::IVehicle::SetBodyHealth>("bodyHealth");
    tpl.Property<&alt::IVehicle::GetBodyAdditionalHealth, &alt::IVehicle::SetBodyAdditionalHealth>("bodyAdditionalHealth");
    tpl.Property<&alt::IVehicle::IsManualEngineControl, &alt::IVehicle::SetManualEngineControl>("manualEngineControl");
    tpl.Property<&alt::IVehicle::GetDamageDataBase64, &alt::IVehicle::LoadDamageDataFromBase64>("damageDataBase64");
    tpl.Property<&alt::IVehicle::GetScriptDataBase64, &alt::IVehicle::LoadScriptDataFromBase64>("scriptDataBase64");
    tpl.Property<&alt::IVehicle::GetGameStateBase64, &alt::IVehicle::LoadGameStateFromBase64>("gameStateDataBase64");
    tpl.Property<&alt::IVehicle::GetHealthDataBase64, &alt::IVehicle::LoadHealthDataFromBase64>("healthDataBase64");
    tpl.Property<&alt::IVehicle::GetAttached>("attached");
    tpl.Property<&alt::IVehicle::GetAttachedTo>("attachedTo");
    tpl.Property<&alt::IVehicle::IsDriftMode, &alt::IVehicle::SetDriftMode>("driftMode");
    // todo: add train stuff
    tpl.Property<&alt::IVehicle::IsBoatAnchorActive, &alt::IVehicle::SetBoatAnchorActive>("boatAnchorActive");
    tpl.Property<&alt::IVehicle::GetLightState, &alt::IVehicle::SetLightState>("lightState");
    tpl.Property<&alt::IVehicle::HasTimedExplosion>("hasTimedExplosion");
    tpl.Property<&alt::IVehicle::GetTimedExplosionCulprit>("timedExplosionCulprit");
    tpl.Property<&alt::IVehicle::GetTimedExplosionTime>("timedExplosionTime");
    tpl.Property<&alt::IVehicle::IsTowingDisabled, &alt::IVehicle::SetDisableTowing>("towingDisabled");
    tpl.Property<&alt::IVehicle::GetRocketRefuelSpeed, &alt::IVehicle::SetRocketRefuelSpeed>("rocketRefuelSpeed");
    tpl.Property<&alt::IVehicle::GetCounterMeasureCount, &alt::IVehicle::SetCounterMeasureCount>("counterMeasureCount");
    tpl.Property<&alt::IVehicle::GetScriptMaxSpeed, &alt::IVehicle::SetScriptMaxSpeed>("scriptMaxSpeed");
    tpl.Property<&alt::IVehicle::GetHybridExtraActive, &alt::IVehicle::SetHybridExtraActive>("hybridExtraActive");
    tpl.Property<&alt::IVehicle::GetHybridExtraState, &alt::IVehicle::SetHybridExtraState>("hybridExtraState");
    tpl.Property<&alt::IVehicle::GetQuaternion, &alt::IVehicle::SetQuaternion>("quaternion");

    tpl.Method<&alt::IVehicle::SetFixed>("repair");
    tpl.Method("setMod", &SetMod);
    tpl.Method<&alt::IVehicle::SetWheels>("setWheels");
    tpl.Method<&alt::IVehicle::SetDoorState>("setDoorState");
    tpl.Method<&alt::IVehicle::SetWindowOpened>("setWindowOpened");
    tpl.Method<&alt::IVehicle::SetWheelBurst>("setWheelBurst");
    tpl.Method<&alt::IVehicle::SetWheelDetached>("setWheelDetached");
    tpl.Method<&alt::IVehicle::SetWheelOnFire>("setWheelOnFire");
    tpl.Method<&alt::IVehicle::SetWheelHealth>("setWheelHealth");
    tpl.Method<&alt::IVehicle::SetWheelFixed>("setWheelFixed");
    tpl.Method<&alt::IVehicle::SetPartDamageLevel>("setPartDamageLevel");
    tpl.Method<&alt::IVehicle::SetPartBulletHoles>("setPartBulletHoles");
    tpl.Method<&alt::IVehicle::SetLightDamaged>("setLightDamaged");
    tpl.Method<&alt::IVehicle::SetWindowDamaged>("setWindowDamaged");
    tpl.Method<&alt::IVehicle::SetSpecialLightDamaged>("setSpecialLightDamaged");
    tpl.Method<&alt::IVehicle::SetArmoredWindowHealth>("setArmoredWindowHealth");
    tpl.Method<&alt::IVehicle::SetArmoredWindowShootCount>("setArmoredWindowShootCount");
    tpl.Method<&alt::IVehicle::SetBumperDamageLevel>("setBumperDamageLevel");
    tpl.Method<&alt::IVehicle::SetSearchLight>("setSearchLight");
    tpl.Method<&alt::IVehicle::SetTimedExplosion>("setTimedExplosion");
    tpl.Method<&alt::IVehicle::GetWeaponCapacity>("getWeaponCapacity");
    tpl.Method<&alt::IVehicle::SetWeaponCapacity>("setWeaponCapacity");

    tpl.StaticFunction("getByID", &GetByID);
});
