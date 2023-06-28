#include "Class.h"

static void GetWheelCamber(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelCamber(wheel));
}

static void SetWheelCamber(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelCamber(wheel, value);
}

static void GetWheelTrackWidth(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelTrackWidth(wheel));
}

static void SetWheelTrackWidth(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelTrackWidth(wheel, value);
}

static void GetWheelHeight(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelHeight(wheel));
}

static void SetWheelHeight(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelHeight(wheel, value);
}

static void GetWheelTyreRadius(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelTyreRadius(wheel));
}

static void SetWheelTyreRadius(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelTyreRadius(wheel, value);
}

static void GetWheelRimRadius(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelRimRadius(wheel));
}

static void SetWheelRimRadius(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelRimRadius(wheel, value);
}

static void GetWheelTyreWidth(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelTyreWidth(wheel));
}

static void SetWheelTyreWidth(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(2)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    float value;
    if(!ctx.GetArg(1, value)) return;

    vehicle->SetWheelTyreWidth(wheel, value);
}

static void GetWheelSurfaceMaterial(js::FunctionContext& ctx)
{
    if(!ctx.CheckThis()) return;
    if(!ctx.CheckArgCount(1)) return;
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();

    uint32_t wheel;
    if(!ctx.GetArg(0, wheel)) return;

    ctx.Return(vehicle->GetWheelSurfaceMaterial(wheel));
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
