#include "Class.h"

static void ModelGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::ILocalPed* ped = ctx.GetThisObject<alt::ILocalPed>();

    ctx.Return(ped->GetModel());
}

static void ModelSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::ILocalPed* ped = ctx.GetThisObject<alt::ILocalPed>();

    uint32_t model;
    if(!ctx.GetValueAsHash(model)) return;

    ped->SetModel(model);
}

static void GetByScriptID(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    if (auto obj = alt::ICore::Instance().GetWorldObjectByScriptID(scriptId); obj->GetType() == alt::IBaseObject::Type::LOCAL_PED)
        return ctx.Return(obj);

    ctx.Return(nullptr);
}

// clang-format off
extern js::Class pedClass;
extern js::Class localPedClass("LocalPed", &pedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::LOCAL_PED);

    tpl.Property("model", ModelGetter, ModelSetter);
    tpl.Property<&alt::ILocalPed::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ILocalPed::IsVisible, &alt::ILocalPed::SetVisible>("visible");
    tpl.Property<&alt::ILocalPed::GetScriptID>("scriptID");
    tpl.Property<&alt::ILocalPed::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::LOCAL_PED>();
    tpl.StaticFunction("getByScriptID", &GetByScriptID);
});
