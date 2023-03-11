#include "Class.h"
#include "cpp-sdk/ICore.h"

static void Ctor(js::FunctionContext& ctx)
{
    if(!ctx.CheckCtor()) return;
    if(!ctx.CheckArgCount(1)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    alt::IVehicle* vehicle = alt::ICore::Instance().CreateVehicle(model, { 0, 0, 0 }, { 0, 0, 0 });
    if(!ctx.Check(vehicle != nullptr, "Failed to create vehicle")) return;

    ctx.SetThisObject(vehicle);
}

static void GetID(js::FunctionContext& ctx)
{
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();
    ctx.Return(vehicle->GetID());
}

static void GetModel(js::FunctionContext& ctx)
{
    alt::IVehicle* vehicle = ctx.GetThisObject<alt::IVehicle>();
    ctx.Return(vehicle->GetModel());
}

// clang-format off
extern js::Class sharedVehicleClass;
extern js::Class vehicleClass("Vehicle", &sharedVehicleClass, Ctor, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::VEHICLE);

    tpl.Method("getID", GetID);
    tpl.Method("getModel", GetModel);
    tpl.Property<alt::IEntity, &alt::IEntity::GetModel>("model");
});
