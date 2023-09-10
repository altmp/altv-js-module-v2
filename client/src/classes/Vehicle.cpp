#include "Class.h"

extern js::Class handlingClass;
static void HandlingGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    uint32_t modelHash = ctx.GetExtraInternalFieldJSValue<uint32_t>();

    auto data = alt::ICore::Instance().GetHandlingData(modelHash);
    if(!ctx.Check(data != nullptr, "No HandlingData exists with this hash")) return;

    ctx.Return(handlingClass.Create(ctx.GetContext(), js::JSValue(modelHash)));
}

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.Property<&alt::IVehicle::GetWheelSpeed>("speed");
    tpl.Property<&alt::IVehicle::GetCurrentGear, &alt::IVehicle::SetCurrentGear>("gear");
    tpl.Property<&alt::IVehicle::GetMaxGear>("maxGear");
    tpl.Property<&alt::IVehicle::GetCurrentRPM, &alt::IVehicle::SetCurrentRPM>("rpm");
    tpl.Property<&alt::IVehicle::GetWheelsCount>("wheelsCount");
    tpl.Property<&alt::IVehicle::GetSpeedVector>("speedVector");
    tpl.Property("handling", HandlingGetter);
    tpl.Property<&alt::IVehicle::IsHandlingModified>("isHandlingModified");
    tpl.Property<&alt::IVehicle::GetLightsIndicator, &alt::IVehicle::SetLightsIndicator>("indicatorLights");
    tpl.Property<&alt::IVehicle::GetSeatCount>("seatCount");
    tpl.Property<&alt::IVehicle::GetOccupiedSeatsCount>("occupiedSeatsCount");
    tpl.Property<&alt::IVehicle::IsTaxiLightOn>("isTaxiLightOn");
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
});
