#include "Class.h"

static void AudioCategoryGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudioFilter* filter = ctx.GetThisObject<alt::IAudioFilter>();

    ctx.Return(filter->GetAudCategory());
}

static void AudioCategorySetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudioFilter* filter = ctx.GetThisObject<alt::IAudioFilter>();

    uint32_t category;
    if(!ctx.GetValueAsHash(category)) return;

    filter->SetAudCategory(category);
}

// clang-format off
extern js::Class audioFilterClass("AudioFilter", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_FILTER);

    tpl.Property("audioCategory", AudioCategoryGetter, AudioCategorySetter);

    tpl.LazyProperty<&alt::IAudioFilter::GetHash>("hash");

    tpl.Method<&alt::IAudioFilter::AddRotateEffect>("addRotateEffect");
    tpl.Method<&alt::IAudioFilter::AddVolumeEffect>("addVolumeEffect");
    tpl.Method<&alt::IAudioFilter::AddPeakeqEffect>("addPeakeqEffect");
    tpl.Method<&alt::IAudioFilter::AddDampEffect>("addDampEffect");
    tpl.Method<&alt::IAudioFilter::AddAutowahEffect>("addAutowahEffect");
    tpl.Method<&alt::IAudioFilter::AddPhaserEffect>("addPhaserEffect");
    tpl.Method<&alt::IAudioFilter::AddChorusEffect>("addChorusEffect");
    tpl.Method<&alt::IAudioFilter::AddDistortionEffect>("addDistortionEffect");
    tpl.Method<&alt::IAudioFilter::AddCompressor2Effect>("addCompressor2Effect");
    tpl.Method<&alt::IAudioFilter::AddBqfEffect>("addBqfEffect");
    tpl.Method<&alt::IAudioFilter::AddEcho4Effect>("addEcho4Effect");
    tpl.Method<&alt::IAudioFilter::AddPitchshiftEffect>("addPitchshiftEffect");
    tpl.Method<&alt::IAudioFilter::AddFreeverbEffect>("addFreeverbEffect");
    tpl.Method<&alt::IAudioFilter::RemoveEffect>("removeEffect");

    tpl.GetByID<alt::IBaseObject::Type::AUDIO_FILTER>();
});
