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

// clang-format off
extern js::Class pedClass;
extern js::Class localPedClass("LocalPed", &pedClass, nullptr, [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::PED);

    tpl.Property("model", ModelGetter, ModelSetter);
    tpl.Property<&alt::ILocalPed::GetStreamingDistance>("streamingDistance");
    tpl.Property<&alt::ILocalPed::IsVisible, &alt::ILocalPed::SetVisible>("visible");
    tpl.Property<&alt::ILocalPed::GetScriptID>("scriptID");
    tpl.Property<&alt::ILocalPed::IsStreamedIn>("isStreamedIn");

    tpl.GetByID<alt::IBaseObject::Type::PED>();
});
