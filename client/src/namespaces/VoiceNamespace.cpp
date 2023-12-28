#include "Namespace.h"

static void InputMutedGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsVoiceInputMuted());
}

static void InputMutedSetter(js::PropertyContext& ctx)
{
    bool muted;
    if(!ctx.GetValue(muted)) return;
    alt::ICore::Instance().SetVoiceInputMuted(muted);
}

static void ActivityInputEnabledGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsVoiceActivationEnabled());
}

static void ActivityInputEnabledSetter(js::PropertyContext& ctx)
{
    bool enabled;
    if(!ctx.GetValue(enabled)) return;
    alt::ICore::Instance().ToggleVoiceActivation(enabled);
}

static void ActivationLevelGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetVoiceActivationLevel());
}

static void ActivationLevelSetter(js::PropertyContext& ctx)
{
    float level;
    if(!ctx.GetValue(level)) return;
    alt::ICore::Instance().SetVoiceActivationLevel(level);
}

static void ActivationKeyGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetVoiceActivationKey());
}

static void VoiceControlsEnabledGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().AreVoiceControlsEnabled());
}

static void NoiseSuppressionEnabledGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsNoiseSuppressionEnabled());
}

static void NoiseSuppressionEnabledSetter(js::PropertyContext& ctx)
{
    bool enabled;
    if(!ctx.GetValue(enabled)) return;
    alt::ICore::Instance().ToggleNoiseSuppression(enabled);
}

static void InputDeviceGetter(js::PropertyContext& ctx)
{
    std::optional<std::string> uid;
    if(!ctx.Check(alt::ICore::Instance().GetActiveVoiceInputDevice(uid), "Missing voice permissions")) return;

    ctx.Return(uid);
}

static void InputDeviceSetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckValueType({ js::Type::NULL_TYPE, js::Type::STRING })) return;

    if(ctx.GetValueType() == js::Type::NULL_TYPE)
    {
        alt::ICore::Instance().SetActiveVoiceInputDevice(std::nullopt);
        return;
    }
    std::string uid;
    if(!ctx.GetValue(uid)) return;
    alt::ICore::Instance().SetActiveVoiceInputDevice(uid);
}

static void AvailableInputDevicesGetter(js::PropertyContext& ctx)
{
    std::vector<alt::SoundDeviceInfo> devices;
    if(!ctx.Check(alt::ICore::Instance().GetVoiceInputDeviceList(devices), "Missing voice permissions")) return;

    js::Array devicesArr(devices.size());
    for(auto& device : devices)
    {
        js::Object deviceObj;
        deviceObj.Set("uid", device.uid);
        deviceObj.Set("name", device.name);

        devicesArr.Push(deviceObj);
    }

    ctx.Return(devicesArr);
}

static void VoicePlayersGetter(js::PropertyContext& ctx)
{
    auto players = alt::ICore::Instance().GetVoicePlayers();

    js::Array playersArr(players.size());
    for(auto& remoteId : players)
        playersArr.Push(remoteId);

    ctx.Return(playersArr);
}

static void ToggleInput(js::FunctionContext& ctx)
{
    bool enabled;
    if(!ctx.GetArg(0, enabled)) return;
    alt::ICore::Instance().ToggleVoiceInput(enabled);
}

static void RemoveVoicePlayer(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    alt::ICore::Instance().RemoveVoicePlayer(remoteId);
}

static void GetPlayerSpatialVolume(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    ctx.Return(alt::ICore::Instance().GetVoiceSpatialVolume(remoteId));
}

static void SetPlayerSpatialVolume(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(2)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    float volume;
    if (!ctx.GetArg(2, volume)) return;

    alt::ICore::Instance().SetVoiceSpatialVolume(remoteId, volume);
}

static void GetPlayerNonSpatialVolume(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    ctx.Return(alt::ICore::Instance().GetVoiceNonSpatialVolume(remoteId));
}

static void SetPlayerNonSpatialVolume(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(2)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    float volume;
    if (!ctx.GetArg(2, volume)) return;

    alt::ICore::Instance().SetVoiceNonSpatialVolume(remoteId, volume);
}

static void AddPlayerFilter(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(2)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    alt::IAudioFilter* filter;
    if (!ctx.GetArg(2, filter)) return;

    alt::ICore::Instance().AddVoiceFilter(remoteId, filter);
}

static void RemovePlayerFilter(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    alt::ICore::Instance().RemoveVoiceFilter(remoteId);
}

static void GetPlayerFilter(js::FunctionContext& ctx)
{
    if (!ctx.CheckArgCount(1)) return;

    uint32_t remoteId;
    if (!ctx.GetArg(1, remoteId)) return;

    ctx.Return(alt::ICore::Instance().GetVoiceFilter(remoteId));
}

// clang-format off
extern js::Namespace voiceNamespace("Voice", [](js::NamespaceTemplate& tpl) {
    tpl.StaticProperty("inputMuted", InputMutedGetter, InputMutedSetter);
    tpl.StaticProperty("activityInputEnabled", ActivityInputEnabledGetter, ActivityInputEnabledSetter);
    tpl.StaticProperty("activationLevel", ActivationLevelGetter, ActivationLevelSetter);
    tpl.StaticProperty("activationKey", ActivationKeyGetter);
    tpl.StaticProperty("voiceControlsEnabled", VoiceControlsEnabledGetter);
    tpl.StaticProperty("noiseSuppressionEnabled", NoiseSuppressionEnabledGetter, NoiseSuppressionEnabledSetter);
    tpl.StaticProperty("inputDevice", InputDeviceGetter, InputDeviceSetter);
    tpl.StaticProperty("availableInputDevices", AvailableInputDevicesGetter);
    tpl.StaticProperty("voicePlayers", VoicePlayersGetter);

    tpl.StaticFunction("toggleInput", ToggleInput);
    tpl.StaticFunction("removeVoicePlayer", RemoveVoicePlayer);

    tpl.StaticFunction("getPlayerSpatialVolume", GetPlayerSpatialVolume);
    tpl.StaticFunction("setPlayerSpatialVolume", SetPlayerSpatialVolume);

    tpl.StaticFunction("getPlayerNonSpatialVolume", GetPlayerNonSpatialVolume);
    tpl.StaticFunction("setPlayerNonSpatialVolume", SetPlayerNonSpatialVolume);

    tpl.StaticFunction("addPlayerFilter", AddPlayerFilter);
    tpl.StaticFunction("removePlayerFilter", RemovePlayerFilter);
    tpl.StaticFunction("getPlayerFilter", GetPlayerFilter);
});
