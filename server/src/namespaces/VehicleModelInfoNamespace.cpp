#include "Namespace.h"

static void DoesExtraExist(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::Object thisObj = ctx.GetThis();
    uint32_t model = thisObj.Get<uint32_t>("model");
    const alt::VehicleModelInfo& info = alt::ICore::Instance().GetVehicleModelByHash(model);
    if(!ctx.Check(info.modelType != alt::VehicleModelInfo::Type::INVALID, "Invalid vehicle model")) return;

    uint8_t extraId;
    if(!ctx.GetArg(0, extraId)) return;

    ctx.Return(info.DoesExtraExist(extraId));
}

static void IsExtraDefault(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::Object thisObj = ctx.GetThis();
    uint32_t model = thisObj.Get<uint32_t>("model");
    const alt::VehicleModelInfo& info = alt::ICore::Instance().GetVehicleModelByHash(model);
    if(!ctx.Check(info.modelType != alt::VehicleModelInfo::Type::INVALID, "Invalid vehicle model")) return;

    uint8_t extraId;
    if(!ctx.GetArg(0, extraId)) return;

    ctx.Return(info.DoesExtraDefault(extraId));
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    const alt::VehicleModelInfo& info = alt::ICore::Instance().GetVehicleModelByHash(model);
    if(!ctx.Check(info.modelType != alt::VehicleModelInfo::Type::INVALID, "Invalid vehicle model")) return;

    v8::Local<v8::Context> context = ctx.GetContext();

    js::Object modelObj;
    modelObj.Set("model", model);
    modelObj.Set("title", info.title);
    modelObj.Set("modelType", info.modelType);
    modelObj.Set("wheelsCount", info.wheelsCount);
    modelObj.Set("hasArmoredWindows", info.hasArmoredWindows);
    modelObj.Set("primaryColor", info.primaryColor);
    modelObj.Set("secondaryColor", info.secondaryColor);
    modelObj.Set("pearlColor", info.pearlColor);
    modelObj.Set("wheelsColor", info.wheelsColor);
    modelObj.Set("interiorColor", info.interiorColor);
    modelObj.Set("dashboardColor", info.dashboardColor);
    js::Array modkits;
    for(uint16_t modkit : info.modkits)
    {
        modkits.Push(modkit != 0xFFFF);
    }
    modelObj.Set("modkits", modkits);
    modelObj.Set("extras", info.extras);
    modelObj.Set("defaultExtras", info.defaultExtras);
    modelObj.Set("hasAutoAttachTrailer", info.hasAutoAttachTrailer);
    js::Array bones;
    for(const alt::BoneInfo& bone : info.bones)
    {
        js::Object boneObj;
        boneObj.Set("id", bone.id);
        boneObj.Set("index", bone.index);
        boneObj.Set("name", bone.name);
        bones.Push(boneObj);
    }
    modelObj.Set("bones", bones);
    modelObj.Set("doesExtraExist", js::WrapFunction(DoesExtraExist)->GetFunction(context).ToLocalChecked());
    modelObj.Set("isExtraDefault", js::WrapFunction(IsExtraDefault)->GetFunction(context).ToLocalChecked());

    ctx.Return(modelObj);
}

// clang-format off
extern js::Namespace vehicleModelInfoNamespace("VehicleModelInfo", [](js::NamespaceTemplate& tpl) {
    tpl.StaticFunction("get", Get);
});
