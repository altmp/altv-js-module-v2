#include "Class.h"

extern js::Class handlingClass;
static void HandlingGetter(js::LazyPropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    ctx.Return(handlingClass.Create(ctx.GetContext(), vehicle));
}

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId);
    if (obj && (obj->GetType() == alt::IBaseObject::Type::VEHICLE || obj->GetType() == alt::IBaseObject::Type::LOCAL_VEHICLE))
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.LazyProperty("handling", HandlingGetter);

    tpl.Property<&alt::IVehicle::GetWheelSpeed>("speed");
    tpl.Property<&alt::IVehicle::GetCurrentGear, &alt::IVehicle::SetCurrentGear>("gear");
    tpl.Property<&alt::IVehicle::GetMaxGear>("maxGear");
    tpl.Property<&alt::IVehicle::GetCurrentRPM, &alt::IVehicle::SetCurrentRPM>("rpm");
    tpl.Property<&alt::IVehicle::GetWheelsCount>("wheelsCount");
    tpl.Property<&alt::IVehicle::GetSpeedVector>("speedVector");
    tpl.Property<&alt::IVehicle::IsHandlingModified>("handlingModified");
    tpl.Property<&alt::IVehicle::GetLightsIndicator, &alt::IVehicle::SetLightsIndicator>("indicatorLights");
    tpl.Property<&alt::IVehicle::GetSeatCount>("seatCount");
    tpl.Property<&alt::IVehicle::GetOccupiedSeatsCount>("occupiedSeatsCount");
    tpl.Property<&alt::IVehicle::IsTaxiLightOn>("taxiLightOn");
    tpl.Property<&alt::IVehicle::GetEngineTemperature, &alt::IVehicle::SetEngineTemperature>("engineTemperature");
    tpl.Property<&alt::IVehicle::GetFuelLevel, &alt::IVehicle::SetFuelLevel>("fuelLevel");
    tpl.Property<&alt::IVehicle::GetOilLevel, &alt::IVehicle::SetOilLevel>("oilLevel");
    tpl.Property<&alt::IVehicle::GetEngineLightState, &alt::IVehicle::SetEngineLightState>("engineLightState");
    tpl.Property<&alt::IVehicle::GetAbsLightState, &alt::IVehicle::SetAbsLightState>("absLightState");
    tpl.Property<&alt::IVehicle::GetPetrolLightState, &alt::IVehicle::SetPetrolLightState>("petrolLightState");
    tpl.Property<&alt::IVehicle::GetOilLightState, &alt::IVehicle::SetOilLightState>("oilLightState");
    tpl.Property<&alt::IVehicle::GetBatteryLightState, &alt::IVehicle::SetBatteryLightState>("batteryLightState");
    tpl.Property<&alt::IVehicle::GetSuspensionHeight, &alt::IVehicle::SetSuspensionHeight>("suspensionHeight");

    tpl.Property<&alt::IVehicle::GetSteeringAngle, &alt::IVehicle::SetSteeringAngle>("steeringAngle");

    tpl.Method<&alt::IVehicle::ResetHandling>("resetHandling");
    tpl.Method<&alt::IVehicle::ReplaceHandling>("replaceHandling");
    tpl.Method<&alt::IVehicle::ToggleTaxiLight>("toggleTaxiLight");
    tpl.Method<&alt::IVehicle::GetWheelCamber>("getWheelCamber");
    tpl.Method<&alt::IVehicle::SetWheelCamber>("setWheelCamber");
    tpl.Method<&alt::IVehicle::GetWheelTrackWidth>("getWheelTrackWidth");
    tpl.Method<&alt::IVehicle::SetWheelTrackWidth>("setWheelTrackWidth");
    tpl.Method<&alt::IVehicle::GetWheelHeight>("getWheelHeight");
    tpl.Method<&alt::IVehicle::SetWheelHeight>("setWheelHeight");
    tpl.Method<&alt::IVehicle::GetWheelTyreRadius>("getWheelTyreRadius");
    tpl.Method<&alt::IVehicle::SetWheelTyreRadius>("setWheelTyreRadius");
    tpl.Method<&alt::IVehicle::GetWheelRimRadius>("getWheelRimRadius");
    tpl.Method<&alt::IVehicle::SetWheelRimRadius>("setWheelRimRadius");
    tpl.Method<&alt::IVehicle::GetWheelTyreWidth>("getWheelTyreWidth");
    tpl.Method<&alt::IVehicle::SetWheelTyreWidth>("setWheelTyreWidth");
    tpl.Method<&alt::IVehicle::GetWheelSurfaceMaterial>("getWheelSurfaceMaterial");
    tpl.Method<&alt::IVehicle::ResetDashboardLights>("resetDashboardLights");

    tpl.GetByID<alt::IBaseObject::Type::VEHICLE>();
    tpl.GetByRemoteID<alt::IBaseObject::Type::VEHICLE>();
    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
