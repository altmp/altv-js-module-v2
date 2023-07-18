#include "Module.h"
#include "interfaces/IResource.h"
#include "interfaces/IAltResource.h"

static void AreGameControlsActive(js::FunctionContext& ctx)
{
    ctx.Return(ctx.GetResource()->GetResource()->GameControlsActive());
}

static void SetGameControlsActive(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool val;
    if(!ctx.GetArg(0, val)) return;

    ctx.GetResource()->GetResource()->ToggleGameControls(val);
}

static void LocaleGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetLocale());
}

static void IsStreamerModeEnabledGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsInStreamerMode());
}

static void IsMenuOpenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsMenuOpen());
}

static void IsConsoleOpenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsConsoleOpen());
}

static void GetMsPerGameMinute(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMsPerGameMinute());
}

static void SetMsPerGameMinute(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    int32_t msPerGameMinute;
    if(!ctx.GetArg(0, msPerGameMinute)) return;

    alt::ICore::Instance().SetMsPerGameMinute(msPerGameMinute);
}

static void LicenseHashGetter(js::LazyPropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetLicenseHash());
}

static void ClientConfigGetter(js::LazyPropertyContext& ctx)
{
    Config::Value::ValuePtr config = alt::ICore::Instance().GetClientConfig();
    v8::Local<v8::Value> configVal = js::ConfigValueToJS(config);
    if(!ctx.Check(!configVal.IsEmpty(), "Failed to convert config")) return;
    ctx.Return(configVal);
}

static void IsGameFocusedGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsGameFocused());
}

static void FpsGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetFps());
}

static void PingGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetPing());
}

static void TotalPacketsSentGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetTotalPacketsSent());
}

static void TotalPacketsLostGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetTotalPacketsLost());
}

static void ServerIpGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetServerIp());
}

static void ServerPortGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetServerPort());
}

static void ClientPathGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetClientPath());
}

static void AreRmlControlsActive(js::FunctionContext& ctx)
{
    ctx.Return(alt::ICore::Instance().AreRmlControlsEnabled());
}

static void SetRmlControlsActive(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool val;
    if(!ctx.GetArg(0, val)) return;

    alt::ICore::Instance().ToggleRmlControls(val);
}

static void ScreenResolutionGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetScreenResolution());
}

static void IsFullscreenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsFullScreen());
}

static void GetKeyState(js::FunctionContext& ctx)
{
    uint32_t keyCode;
    if(!ctx.GetArg(0, keyCode)) return;

    alt::KeyState state = alt::ICore::Instance().GetKeyState(keyCode);
    js::Object obj;
    obj.Set("isDown", state.IsDown());
    obj.Set("isToggled", state.IsToggled());

    ctx.Return(obj);
}

static void DoesConfigFlagExist(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    ctx.Return(alt::ICore::Instance().DoesConfigFlagExist(flag));
}

static void BeginScaleformMovieMethodMinimap(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string method;
    if(!ctx.GetArg(0, method)) return;

    alt::ICore::Instance().BeginScaleformMovieMethodMinimap(method);
}

static void SetWeatherCycle(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    js::Array weathersArr;
    if(!ctx.GetArg(0, weathersArr)) return;

    std::vector<uint8_t> weathers;
    weathers.reserve(weathersArr.Length());
    std::vector<uint8_t> multipliers;
    multipliers.reserve(weathersArr.Length());
    for(int i = 0; i < weathersArr.Length(); i++)
    {
        js::Object obj;
        if(!weathersArr.Get(i, obj)) return;

        uint8_t weather;
        if(!obj.Get("weather", weather)) return;
        uint8_t multiplier;
        if(!obj.Get("multiplier", multiplier)) return;

        weathers.push_back(weather);
        multipliers.push_back(multiplier);
    }

    alt::ICore::Instance().SetWeatherCycle(weathers, multipliers);
}

static void GetConfigFlag(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    ctx.Return(alt::ICore::Instance().GetConfigFlag(flag));
}

static void SetConfigFlag(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    bool state;
    if(!ctx.GetArg(1, state)) return;

    ctx.Return(alt::ICore::Instance().SetConfigFlag(flag, state));
}

static void SetWeatherSyncActive(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool state;
    if(!ctx.GetArg(0, state)) return;

    alt::ICore::Instance().SetWeatherSyncActive(state);
}

static void GetPermissionState(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    alt::Permission permission;
    if(!ctx.GetArg(0, permission)) return;

    ctx.Return(alt::ICore::Instance().GetPermissionState(permission));
}

static void TakeScreenshot(js::FunctionContext& ctx)
{
    static std::set<js::Promise*> promises;
    bool gameOnly = ctx.GetArg<bool>(0, false);

    js::Promise* promise = new js::Promise;
    js::IAltResource* resource = ctx.GetResource<js::IAltResource>();

    auto callback = [=](const std::string& base64Str)
    {
        std::string base64 = base64Str;
        resource->PushNextTickCallback(
          [=]()
          {
              promise->Resolve(base64);
              promises.erase(promise);
          });
    };
    if(!gameOnly) alt::ICore::Instance().TakeScreenshot(callback);
    else
        alt::ICore::Instance().TakeScreenshotGameOnly(callback);

    promises.insert(promise);
    ctx.Return(promise->Get());
}

static void SetAngularVelocity(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    uint32_t entity;
    if(!ctx.GetArg(0, entity)) return;

    alt::Quaternion quat;
    if(!ctx.GetArg(1, quat)) return;

    alt::ICore::Instance().SetAngularVelocity(entity, { quat.x, quat.y, quat.z, quat.w });
}

static void HeadshotToBase64(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t id;
    if(!ctx.GetArg(0, id)) return;

    ctx.Return(alt::ICore::Instance().HeadshotToBase64(id));
}

static void SetDlcClothes(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(4, 6)) return;

    int32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    uint8_t component;
    if(!ctx.GetArg(1, component)) return;

    uint16_t drawable;
    if(!ctx.GetArg(2, drawable)) return;

    uint16_t texture;
    if(!ctx.GetArg(3, texture)) return;

    uint8_t palette = ctx.GetArg<uint8_t>(4, 2);
    uint32_t dlc = ctx.GetArg<uint32_t>(5, 0);

    alt::ICore::Instance().SetDlcClothes(scriptId, component, drawable, texture, palette, dlc);
}

static void SetDlcProps(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(4, 5)) return;

    int32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    uint8_t component;
    if(!ctx.GetArg(1, component)) return;

    uint16_t drawable;
    if(!ctx.GetArg(2, drawable)) return;

    uint16_t texture;
    if(!ctx.GetArg(3, texture)) return;

    uint32_t dlc = ctx.GetArg<uint32_t>(4, 0);

    alt::ICore::Instance().SetDlcProps(scriptId, component, drawable, texture, dlc);
}

static void ClearProps(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    int32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    uint8_t component;
    if(!ctx.GetArg(1, component)) return;

    alt::ICore::Instance().ClearProps(scriptId, component);
}

static void SetWatermarkPosition(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    uint8_t position;
    if(!ctx.GetArg(0, position)) return;

    alt::ICore::Instance().SetWatermarkPosition(position);
}

static void CopyToClipboard(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string str;
    if(!ctx.GetArg(0, str)) return;

    alt::ICore::Instance().CopyToClipboard(str);
}

static void ToggleRmlDebugger(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool state;
    if(!ctx.GetArg(0, state)) return;

    alt::ICore::Instance().ToggleRmlDebugger(state);
}

static void LoadRmlFontFace(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2, 4)) return;

    std::string path;
    if(!ctx.GetArg(0, path)) return;

    std::string name;
    if(!ctx.GetArg(1, name)) return;

    bool italic = ctx.GetArg<bool>(2, false);
    bool bold = ctx.GetArg<bool>(3, false);

    js::SourceLocation location = js::SourceLocation::GetCurrent(ctx.GetResource());
    alt::ICore::Instance().LoadRmlFontFace(ctx.GetResource()->GetResource(), path, location.file, name, italic, bold);
}

static void WorldToScreen(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    alt::Vector3f pos;
    if(!ctx.GetArg(0, pos)) return;

    ctx.Return(alt::ICore::Instance().WorldToScreen(pos));
}

static void ScreenToWorld(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    alt::Vector2f pos;
    if(!ctx.GetArg(0, pos)) return;

    ctx.Return(alt::ICore::Instance().ScreenToWorld(pos));
}

static void SetMinimapComponentPosition(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(5)) return;

    std::string name;
    if(!ctx.GetArg(0, name)) return;

    std::string alignX;
    if(!ctx.GetArg(1, alignX)) return;

    std::string alignY;
    if(!ctx.GetArg(2, alignY)) return;

    alt::Vector2f pos;
    if(!ctx.GetArg(3, pos)) return;

    alt::Vector2f size;
    if(!ctx.GetArg(4, size)) return;

    alt::ICore::Instance().SetMinimapComponentPosition(name, alignX[0], alignY[0], pos, size);
}

static void SetMinimapIsRectangle(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    bool state;
    if(!ctx.GetArg(1, state)) return;

    alt::ICore::Instance().SetMinimapIsRectangle(state);
}

static void GetPedBonePos(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    int32_t scriptId;
    if(!ctx.GetArg(0, scriptId)) return;

    uint16_t boneId;
    if(!ctx.GetArg(1, boneId)) return;

    ctx.Return(alt::ICore::Instance().GetPedBonePos(scriptId, boneId));
}

static void LocalMetaGetter(js::DynamicPropertyGetterContext& ctx)
{
    if(!ctx.CheckParent()) return;

    alt::MValue val = alt::ICore::Instance().GetLocalMetaData(ctx.GetProperty());
    ctx.Return(val);
}

// clang-format off
extern js::Class playerClass, localPlayerClass, vehicleClass, pedClass, networkObjectClass,
                audioClass, audioFilterClass, blipClass, textLabelClass, checkpointClass, webViewClass, fontClass,
                localPedClass, localVehicleClass, rmlDocumentClass, rmlElementClass, objectClass, webSocketClientClass,
                mapZoomDataClass, virtualEntityClass, virtualEntityGroupClass, weaponDataClass, handlingClass, handlingDataClass,
                httpClientClass, audioOutputClass, audioOutputAttachedClass, audioOutputFrontendClass, audioOutputWorldClass, audioCategoryClass;
extern js::Namespace eventsNamespace, discordNamespace, voiceNamespace, localStorageNamespace, statsNamespace, focusDataNamespace,
                    gxtNamespace, cursorNamespace, camNamespace, streamingNamespace;
static js::Module altModule("@altv/client", "@altv/shared",
    { &playerClass, &localPlayerClass, &vehicleClass, &pedClass, &networkObjectClass,
    &audioClass, &audioFilterClass, &blipClass, &textLabelClass, &checkpointClass, &webViewClass, &fontClass,
    &localPedClass, &localVehicleClass, &rmlDocumentClass, &rmlElementClass, &objectClass, &webSocketClientClass,
    &mapZoomDataClass, &virtualEntityClass, &virtualEntityGroupClass, &weaponDataClass, &handlingClass, &handlingDataClass,
    &httpClientClass, &audioOutputClass, &audioOutputAttachedClass, &audioOutputFrontendClass, &audioOutputWorldClass, &audioCategoryClass },
[](js::ModuleTemplate& module) {
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);
    module.StaticProperty("locale", LocaleGetter);
    module.StaticProperty("isStreamerModeEnabled", IsStreamerModeEnabledGetter);
    module.StaticProperty("isMenuOpen", IsMenuOpenGetter);
    module.StaticProperty("isConsoleOpen", IsConsoleOpenGetter);
    module.StaticProperty("isGameFocused", IsGameFocusedGetter);
    module.StaticProperty("fps", FpsGetter);
    module.StaticProperty("ping", PingGetter);
    module.StaticProperty("totalPacketsSent", TotalPacketsSentGetter);
    module.StaticProperty("totalPacketsLost", TotalPacketsLostGetter);
    module.StaticProperty("serverIp", ServerIpGetter);
    module.StaticProperty("serverPort", ServerPortGetter);
    module.StaticProperty("clientPath", ClientPathGetter);
    module.StaticProperty("screenResolution", ScreenResolutionGetter);
    module.StaticProperty("isFullscreen", IsFullscreenGetter);

    module.StaticLazyProperty("licenseHash", LicenseHashGetter);
    module.StaticLazyProperty("clientConfig", ClientConfigGetter);

    module.StaticFunction("areGameControlsActive", AreGameControlsActive);
    module.StaticFunction("setGameControlsActive", SetGameControlsActive);
    module.StaticFunction("getMsPerGameMinute", GetMsPerGameMinute);
    module.StaticFunction("setMsPerGameMinute", SetMsPerGameMinute);
    module.StaticFunction("areRmlControlsActive", AreRmlControlsActive);
    module.StaticFunction("setRmlControlsActive", SetRmlControlsActive);
    module.StaticFunction("getKeyState", GetKeyState);
    module.StaticFunction("getConfigFlag", GetConfigFlag);
    module.StaticFunction("setConfigFlag", SetConfigFlag);
    module.StaticFunction("doesConfigFlagExist", DoesConfigFlagExist);
    module.StaticFunction("beginScaleformMovieMethodMinimap", BeginScaleformMovieMethodMinimap);
    module.StaticFunction("setWeatherCycle", SetWeatherCycle);
    module.StaticFunction("setWeatherSyncActive", SetWeatherSyncActive);
    module.StaticFunction("getPermissionState", GetPermissionState);
    module.StaticFunction("takeScreenshot", TakeScreenshot);
    module.StaticFunction("setAngularVelocity", SetAngularVelocity);
    module.StaticFunction("headshotToBase64", HeadshotToBase64);
    module.StaticFunction("setDlcClothes", SetDlcClothes);
    module.StaticFunction("setDlcProps", SetDlcProps);
    module.StaticFunction("clearProps", ClearProps);
    module.StaticFunction("setWatermarkPosition", SetWatermarkPosition);
    module.StaticFunction("copyToClipboard", CopyToClipboard);
    module.StaticFunction("toggleRmlDebugger", ToggleRmlDebugger);
    module.StaticFunction("loadRmlFontFace", LoadRmlFontFace);
    module.StaticFunction("worldToScreen", WorldToScreen);
    module.StaticFunction("screenToWorld", ScreenToWorld);
    module.StaticFunction("setMinimapComponentPosition", SetMinimapComponentPosition);
    module.StaticFunction("setMinimapIsRectangle", SetMinimapIsRectangle);
    module.StaticFunction("getPedBonePos", GetPedBonePos);

    module.Namespace(eventsNamespace);
    module.Namespace(discordNamespace);
    module.Namespace(voiceNamespace);
    module.Namespace(localStorageNamespace);
    module.Namespace(statsNamespace);
    module.Namespace(focusDataNamespace);
    module.Namespace(gxtNamespace);
    module.Namespace(cursorNamespace);
    module.Namespace(camNamespace);
    module.Namespace(streamingNamespace);
    module.Namespace("WeaponObject");

    module.StaticDynamicProperty("localMeta", LocalMetaGetter);
});
