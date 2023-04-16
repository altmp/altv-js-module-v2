#include "Class.h"
#include "cpp-sdk/ICore.h"

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

static void GetByID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint16_t id;
    if(!ctx.GetArg(0, id)) return;
    alt::IEntity* entity = alt::ICore::Instance().GetEntityByID(id);
    if(!entity || entity->GetType() != alt::IBaseObject::Type::VEHICLE) ctx.Return(nullptr);
    else
        ctx.Return((alt::IBaseObject*)entity);
}

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.DynamicProperty("neon", nullptr, &NeonSetter, nullptr, nullptr);

    tpl.Property("modKit", &ModKitGetter, &ModKitSetter);
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetPrimaryColor, &alt::IVehicle::SetPrimaryColor>("primaryColor");
    tpl.Property<alt::IVehicle, alt::RGBA, &alt::IVehicle::GetPrimaryColorRGB, &alt::IVehicle::SetPrimaryColorRGB>("customPrimaryColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetSecondaryColor, &alt::IVehicle::SetSecondaryColor>("secondaryColor");
    tpl.Property<alt::IVehicle, alt::RGBA, &alt::IVehicle::GetSecondaryColorRGB, &alt::IVehicle::SetSecondaryColorRGB>("customSecondaryColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetPearlColor, &alt::IVehicle::SetPearlColor>("pearlColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetWheelColor, &alt::IVehicle::SetWheelColor>("wheelColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetInteriorColor, &alt::IVehicle::SetInteriorColor>("interiorColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetDashboardColor, &alt::IVehicle::SetDashboardColor>("dashboardColor");
    tpl.Property<alt::IVehicle, alt::RGBA, &alt::IVehicle::GetTireSmokeColor, &alt::IVehicle::SetTireSmokeColor>("tireSmokeColor");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::GetCustomTires, &alt::IVehicle::SetCustomTires>("customTires");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetSpecialDarkness, &alt::IVehicle::SetSpecialDarkness>("specialDarkness");
    tpl.Property<alt::IVehicle, uint32_t, &alt::IVehicle::GetNumberplateIndex, &alt::IVehicle::SetNumberplateIndex>("numberplateIndex");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetNumberplateText, &alt::IVehicle::SetNumberplateText>("numberplateText");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetWindowTint, &alt::IVehicle::SetWindowTint>("windowTint");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetDirtLevel, &alt::IVehicle::SetDirtLevel>("dirtLevel");
    tpl.Property<alt::IVehicle, alt::RGBA, &alt::IVehicle::GetNeonColor, &alt::IVehicle::SetNeonColor>("neonColor");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetLivery, &alt::IVehicle::SetLivery>("livery");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetRoofLivery, &alt::IVehicle::SetRoofLivery>("roofLivery");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetAppearanceDataBase64, &alt::IVehicle::LoadAppearanceDataFromBase64>("appearanceDataBase64");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsEngineOn, &alt::IVehicle::SetEngineOn>("engineOn");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetHeadlightColor, &alt::IVehicle::SetHeadlightColor>("headlightColor");
    tpl.Property<alt::IVehicle, uint32_t, &alt::IVehicle::GetRadioStationIndex, &alt::IVehicle::SetRadioStationIndex>("radioStationIndex");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsSirenActive, &alt::IVehicle::SetSirenActive>("sirenActive");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetLockState, &alt::IVehicle::SetLockState>("lockState");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetRoofState, &alt::IVehicle::SetRoofState>("roofState");
    tpl.Property<alt::IVehicle, float, &alt::IVehicle::GetLightsMultiplier, &alt::IVehicle::SetLightsMultiplier>("lightsMultiplier");
    tpl.Property<alt::IVehicle, int32_t, &alt::IVehicle::GetEngineHealth, &alt::IVehicle::SetEngineHealth>("engineHealth");
    tpl.Property<alt::IVehicle, int32_t, &alt::IVehicle::GetPetrolTankHealth, &alt::IVehicle::SetPetrolTankHealth>("petrolTankHealth");
    tpl.Property<alt::IVehicle, uint32_t, &alt::IVehicle::GetBodyHealth, &alt::IVehicle::SetBodyHealth>("bodyHealth");
    tpl.Property<alt::IVehicle, uint32_t, &alt::IVehicle::GetBodyAdditionalHealth, &alt::IVehicle::SetBodyAdditionalHealth>("bodyAdditionalHealth");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsManualEngineControl, &alt::IVehicle::SetManualEngineControl>("manualEngineControl");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetDamageDataBase64, &alt::IVehicle::LoadDamageDataFromBase64>("damageDataBase64");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetScriptDataBase64, &alt::IVehicle::LoadScriptDataFromBase64>("scriptDataBase64");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetGameStateBase64, &alt::IVehicle::LoadGameStateFromBase64>("gameStateDataBase64");
    tpl.Property<alt::IVehicle, std::string, const std::string&, &alt::IVehicle::GetHealthDataBase64, &alt::IVehicle::LoadHealthDataFromBase64>("healthDataBase64");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetAttached>("attached");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetAttachedTo>("attachedTo");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsDriftMode, &alt::IVehicle::SetDriftMode>("driftMode");
    // todo: add train stuff
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsBoatAnchorActive, &alt::IVehicle::SetBoatAnchorActive>("boatAnchorActive");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetLightState, &alt::IVehicle::SetLightState>("lightState");
    tpl.Property<alt::IVehicle, &alt::IVehicle::HasTimedExplosion>("hasTimedExplosion");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetTimedExplosionCulprit>("timedExplosionCulprit");
    tpl.Property<alt::IVehicle, &alt::IVehicle::GetTimedExplosionTime>("timedExplosionTime");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::IsTowingDisabled, &alt::IVehicle::SetDisableTowing>("towingDisabled");
    tpl.Property<alt::IVehicle, float, &alt::IVehicle::GetRocketRefuelSpeed, &alt::IVehicle::SetRocketRefuelSpeed>("rocketRefuelSpeed");
    tpl.Property<alt::IVehicle, uint32_t, &alt::IVehicle::GetCounterMeasureCount, &alt::IVehicle::SetCounterMeasureCount>("counterMeasureCount");
    tpl.Property<alt::IVehicle, float, &alt::IVehicle::GetScriptMaxSpeed, &alt::IVehicle::SetScriptMaxSpeed>("scriptMaxSpeed");
    tpl.Property<alt::IVehicle, bool, &alt::IVehicle::GetHybridExtraActive, &alt::IVehicle::SetHybridExtraActive>("hybridExtraActive");
    tpl.Property<alt::IVehicle, uint8_t, &alt::IVehicle::GetHybridExtraState, &alt::IVehicle::SetHybridExtraState>("hybridExtraState");
    tpl.Property<alt::IVehicle, alt::Quaternion, &alt::IVehicle::GetQuaternion, &alt::IVehicle::SetQuaternion>("quaternion");

    tpl.Method<alt::IVehicle, void, &alt::IVehicle::SetFixed>("repair");
    tpl.Method<alt::IVehicle, bool, uint8_t, uint8_t, &alt::IVehicle::SetMod>("setMod");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetWheels>("setWheels");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetDoorState>("setDoorState");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetWindowOpened>("setWindowOpened");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetWheelBurst>("setWheelBurst");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetWheelDetached>("setWheelDetached");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetWheelOnFire>("setWheelOnFire");
    tpl.Method<alt::IVehicle, void, uint8_t, float, &alt::IVehicle::SetWheelHealth>("setWheelHealth");
    tpl.Method<alt::IVehicle, void, uint8_t, &alt::IVehicle::SetWheelFixed>("setWheelFixed");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetPartDamageLevel>("setPartDamageLevel");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetPartBulletHoles>("setPartBulletHoles");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetLightDamaged>("setLightDamaged");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetWindowDamaged>("setWindowDamaged");
    tpl.Method<alt::IVehicle, void, uint8_t, bool, &alt::IVehicle::SetSpecialLightDamaged>("setSpecialLightDamaged");
    tpl.Method<alt::IVehicle, void, uint8_t, float, &alt::IVehicle::SetArmoredWindowHealth>("setArmoredWindowHealth");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetArmoredWindowShootCount>("setArmoredWindowShootCount");
    tpl.Method<alt::IVehicle, void, uint8_t, uint8_t, &alt::IVehicle::SetBumperDamageLevel>("setBumperDamageLevel");
    tpl.Method<alt::IVehicle, bool, bool, alt::IEntity*, &alt::IVehicle::SetSearchLight>("setSearchLight");
    tpl.Method<alt::IVehicle, void, bool, alt::IPlayer*, uint32_t, &alt::IVehicle::SetTimedExplosion>("setTimedExplosion");
    tpl.Method<alt::IVehicle, int32_t, uint8_t, &alt::IVehicle::GetWeaponCapacity>("getWeaponCapacity");
    tpl.Method<alt::IVehicle, void, uint8_t, int32_t, &alt::IVehicle::SetWeaponCapacity>("setWeaponCapacity");

    tpl.StaticFunction("getByID", &GetByID);
});
