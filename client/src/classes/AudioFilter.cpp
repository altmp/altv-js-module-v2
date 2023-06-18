#include "Class.h"

// clang-format off
extern js::Class audioFilterClass("AudioFilter", [](js::ClassTemplate& tpl)
{
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
});
