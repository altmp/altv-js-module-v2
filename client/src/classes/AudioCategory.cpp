#include "Class.h"
#include "helpers/ClassInstanceCache.h"

template<auto Method>
static void GenericGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    std::string name = ctx.GetExtraInternalFieldJSValue<std::string>();
    std::shared_ptr<alt::IAudioCategory> category = alt::ICore::Instance().GetAudioCategory(name);

    ctx.Return((category.get()->*Method)());
}

template<auto Method, typename T>
static void GenericSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    std::string name = ctx.GetExtraInternalFieldJSValue<std::string>();
    std::shared_ptr<alt::IAudioCategory> category = alt::ICore::Instance().GetAudioCategory(name);

    T value;
    if(!ctx.GetValue(value)) return;

    (category.get()->*Method)(value);
}

static void Reset(js::FunctionContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldJSValue()) return;
    std::string name = ctx.GetExtraInternalFieldJSValue<std::string>();
    std::shared_ptr<alt::IAudioCategory> category = alt::ICore::Instance().GetAudioCategory(name);

    category->Reset();
}

extern js::Class audioCategoryClass;
extern js::ClassInstanceCache audioCategoryCache(audioCategoryClass);
static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string name;
    if(!ctx.GetArg(0, name)) return;

    std::shared_ptr<alt::IAudioCategory> category = alt::ICore::Instance().GetAudioCategory(name);
    if(!ctx.Check(category != nullptr, "Failed to get audio category")) return;

    uint32_t hash = alt::ICore::Instance().Hash(name);
    ctx.Return(audioCategoryCache.GetOrCreate(ctx.GetResource(), hash, js::JSValue(name)));
}

// clang-format off
extern js::Class audioCategoryClass("AudioCategory", [](js::ClassTemplate& tpl)
{
    tpl.Property("name", GenericGetter<&alt::IAudioCategory::GetName>);
    tpl.Property("volume", GenericGetter<&alt::IAudioCategory::GetVolume>, GenericSetter<&alt::IAudioCategory::SetVolume, float>);
    tpl.Property("distanceRolloffScale", GenericGetter<&alt::IAudioCategory::GetDistanceRolloffScale>, GenericSetter<&alt::IAudioCategory::SetDistanceRolloffScale, float>);
    tpl.Property("plateauRolloffScale", GenericGetter<&alt::IAudioCategory::GetPlateauRolloffScale>, GenericSetter<&alt::IAudioCategory::SetPlateauRolloffScale, float>);
    tpl.Property("occlusionDamping", GenericGetter<&alt::IAudioCategory::GetOcclusionDamping>, GenericSetter<&alt::IAudioCategory::SetOcclusionDamping, float>);
    tpl.Property("environmentalFilterDamping", GenericGetter<&alt::IAudioCategory::GetEnvironmentalFilterDamping>, GenericSetter<&alt::IAudioCategory::SetEnvironmentalFilterDamping, float>);
    tpl.Property("sourceReverbDamping", GenericGetter<&alt::IAudioCategory::GetSourceReverbDamping>, GenericSetter<&alt::IAudioCategory::SetSourceReverbDamping, float>);
    tpl.Property("distanceReverbDamping", GenericGetter<&alt::IAudioCategory::GetDistanceReverbDamping>, GenericSetter<&alt::IAudioCategory::SetDistanceReverbDamping, float>);
    tpl.Property("interiorReverbDamping", GenericGetter<&alt::IAudioCategory::GetInteriorReverbDamping>, GenericSetter<&alt::IAudioCategory::SetInteriorReverbDamping, float>);
    tpl.Property("environmentalLoudness", GenericGetter<&alt::IAudioCategory::GetEnvironmentalLoudness>, GenericSetter<&alt::IAudioCategory::SetEnvironmentalLoudness, float>);
    tpl.Property("underwaterWetLevel", GenericGetter<&alt::IAudioCategory::GetUnderwaterWetLevel>, GenericSetter<&alt::IAudioCategory::SetUnderwaterWetLevel, float>);
    tpl.Property("stonedWetLevel", GenericGetter<&alt::IAudioCategory::GetStonedWetLevel>, GenericSetter<&alt::IAudioCategory::SetStonedWetLevel, float>);
    tpl.Property("pitch", GenericGetter<&alt::IAudioCategory::GetPitch>, GenericSetter<&alt::IAudioCategory::SetPitch, int16_t>);
    tpl.Property("lowPassFilterCutoff", GenericGetter<&alt::IAudioCategory::GetLowPassFilterCutoff>, GenericSetter<&alt::IAudioCategory::SetLowPassFilterCutoff, int16_t>);
    tpl.Property("highPassFilterCutoff", GenericGetter<&alt::IAudioCategory::GetHighPassFilterCutoff>, GenericSetter<&alt::IAudioCategory::SetHighPassFilterCutoff, int16_t>);

    tpl.Method("reset", Reset);

    tpl.StaticFunction("get", Get);
}, true);
