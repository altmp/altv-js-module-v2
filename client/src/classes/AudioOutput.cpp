#include "Class.h"

static void GetFilter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudioOutput* audio = ctx.GetThisObject<alt::IAudioOutput>();

    ctx.Return(audio->GetFilter());
}

static void SetFilter(js::PropertyContext& ctx)
{
    if(!ctx.CheckThis()) return;
    alt::IAudioOutput* output = ctx.GetThisObject<alt::IAudioOutput>();

    if(ctx.GetValueType() == js::Type::NULL_TYPE)
    {
        output->RemoveFilter();
    }
    else if(ctx.GetValueType() == js::Type::BASE_OBJECT)
    {
        alt::IAudioFilter* filter;
        if(!ctx.GetValue(filter)) return;
        output->AddFilter(filter);
    }
    else
    {
        ctx.Throw("AudioOutput.filter setter expects null or AudioFilter object");
    }
}

// clang-format off
extern js::Class audioOutputClass("AudioOutput", [](js::ClassTemplate& tpl)
{
    tpl.BindToType(alt::IBaseObject::Type::AUDIO_OUTPUT);

    tpl.Property<&alt::IAudioOutput::IsMuted, &alt::IAudioOutput::SetMuted>("muted");
    tpl.Property<&alt::IAudioOutput::GetVolume, &alt::IAudioOutput::SetVolume>("volume");
    tpl.Property<&alt::IAudioOutput::GetCategory>("category");
    tpl.Property("filter", &GetFilter, &SetFilter);

    tpl.GetByID<alt::IBaseObject::Type::AUDIO>();
});
