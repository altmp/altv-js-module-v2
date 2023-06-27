#include "Class.h"

static void HandlingGetter(js::PropertyContext& ctx)
{
    extern js::Class Handling;
    ctx.Return(Handling.Create(ctx.GetContext()));
}

template<typename GetterFunc>
static void GetPropertyValue(js::FunctionContext& ctx, GetterFunc getter)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if (!ctx.GetArg(0, wheel)) return;

    ctx.Return(getter(vehicle, wheel));
}

template<typename SetterFunc>
static void SetPropertyValue(js::FunctionContext& ctx, SetterFunc setter)
{
    if (!ctx.CheckThis()) return;
    if (!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if (!ctx.GetArg(0, wheel)) return;

    float value;
    if (!ctx.GetArg(1, value)) return;

    setter(vehicle, wheel, value);
}

static void GetWheelCamber(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelCamber(wheel);
    });
}

static void SetWheelCamber(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelCamber(wheel, value);
    });
}

static void GetWheelTrackWidth(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelTrackWidth(wheel);
    });
}

static void SetWheelTrackWidth(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelTrackWidth(wheel, value);
    });
}

static void GetWheelHeight(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelHeight(wheel);
    });
}

static void SetWheelHeight(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelHeight(wheel, value);
    });
}

static void GetWheelTyreRadius(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelTyreRadius(wheel);
    });
}

static void SetWheelTyreRadius(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelTyreRadius(wheel, value);
    });
}

static void GetWheelRimRadius(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelRimRadius(wheel);
    });
}

static void SetWheelRimRadius(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelRimRadius(wheel, value);
    });
}

static void GetWheelTyreWidth(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelTyreWidth(wheel);
    });
}

static void SetWheelTyreWidth(js::FunctionContext& ctx)
{
    SetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel, float value) {
        vehicle->SetWheelTyreWidth(wheel, value);
    });
}

static void GetWheelSurfaceMaterial(js::FunctionContext& ctx)
{
    GetPropertyValue(ctx, [](alt::IVehicle* vehicle, uint32_t wheel) {
        return vehicle->GetWheelSurfaceMaterial(wheel);
    });
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
    tpl.Property<&alt::IVehicle::IsHandlingModified>("isHandlingModified");
    tpl.Property("handling", HandlingGetter);
    tpl.Property<&alt::IVehicle::GetLightsIndicator, &alt::IVehicle::SetLightsIndicator>("indicatorLights");
    tpl.Property<&alt::IVehicle::GetSeatCount>("seatCount");
    tpl.Property<&alt::IVehicle::GetOccupiedSeatsCount>("occupiedSeatsCount");
    tpl.Property<&alt::IVehicle::IsTaxiLightOn>("TaxiLightOn");
    tpl.Property<&alt::IVehicle::GetEngineTemperature, &alt::IVehicle::SetEngineTemperature>("engineTemperature");
    tpl.Property<&alt::IVehicle::GetFuelLevel, &alt::IVehicle::SetFuelLevel>("fuelLevel");
    tpl.Property<&alt::IVehicle::GetOilLevel, &alt::IVehicle::SetOilLevel>("oilLevel");
    tpl.Property<&alt::IVehicle::GetEngineLightState, &alt::IVehicle::SetEngineLightState>("engineLight");
    tpl.Property<&alt::IVehicle::GetAbsLightState, &alt::IVehicle::SetAbsLightState>("absLight");
    tpl.Property<&alt::IVehicle::GetPetrolLightState, &alt::IVehicle::SetPetrolLightState>("petrolLight");
    tpl.Property<&alt::IVehicle::GetOilLightState, &alt::IVehicle::SetOilLightState>("oilLight");
    tpl.Property<&alt::IVehicle::GetBatteryLightState, &alt::IVehicle::SetBatteryLightState>("batteryLight");

    tpl.Method<&alt::IVehicle::ResetHandling>("resetHandling");
    tpl.Method<&alt::IVehicle::ReplaceHandling>("replaceHandling");
    tpl.Method<&alt::IVehicle::ToggleTaxiLight>("toggleTaxiLight");
    tpl.Method("getWheelCamber", GetWheelCamber);
    tpl.Method("setWheelCamber", SetWheelCamber);
    tpl.Method("getWheelTrackWidth", GetWheelTrackWidth);
    tpl.Method("setWheelTrackWidth", SetWheelTrackWidth);
    tpl.Method("getWheelHeight", GetWheelHeight);
    tpl.Method("setWheelHeight", SetWheelHeight);
    tpl.Method("getWheelTyreRadius", GetWheelTyreRadius);
    tpl.Method("setWheelTyreRadius", SetWheelTyreRadius);
    tpl.Method("getWheelRimRadius", GetWheelRimRadius);
    tpl.Method("setWheelRimRadius", SetWheelRimRadius);
    tpl.Method("getWheelTyreWidth", GetWheelTyreWidth);
    tpl.Method("setWheelTyreWidth", SetWheelTyreWidth);
    tpl.Method("getWheelSurfaceMaterial", GetWheelSurfaceMaterial);
    tpl.Method<&alt::IVehicle::ResetDashboardLights>("resetDashboardLights");

    tpl.GetByID<alt::IBaseObject::Type::VEHICLE>();
});
