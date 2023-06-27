#include "Class.h"

static void ModelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::ILocalVehicle* vehicle = ctx.GetThisObject<alt::ILocalVehicle>();

    ctx.Return(vehicle->GetModel());
}

static void ModelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::ILocalVehicle* vehicle = ctx.GetThisObject<alt::ILocalVehicle>();

    uint32_t model;
    if(!ctx.GetValueAsHash(model)) return;

    vehicle->SetModel(model);
}

// clang-format off
extern js::Class vehicleClass;
extern js::Class localVehicleClass("LocalVehicle", &vehicleClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::LOCAL_VEHICLE);

    tpl.Property("model", ModelGetter, ModelSetter);
    tpl.Property<&alt::ILocalPed::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ILocalPed::IsVisible, &alt::ILocalPed::SetVisible>("visible");
    tpl.Property<&alt::ILocalPed::GetScriptID>("scriptID");
    tpl.Property<&alt::ILocalPed::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::LOCAL_VEHICLE>();
});
