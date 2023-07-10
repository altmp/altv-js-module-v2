#include "Module.h"
#include "interfaces/IResource.h"
#include "interfaces/IAltResource.h"

static void GameControlsActiveGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().AreControlsEnabled());
}

static void GameControlsActiveSetter(js::PropertyContext& ctx)
{
    bool val;
    if(!ctx.GetValue(val)) return;

    ctx.GetResource()->GetResource()->ToggleGameControls(val);
}

static void CursorVisibleGetter(js::PropertyContext& ctx)
{
    ctx.Return(ctx.GetResource()->GetResource()->CursorVisible());
}

static void CursorVisibleSetter(js::PropertyContext& ctx)
{
    bool val;
    if(!ctx.GetValue(val)) return;

    ctx.GetResource()->GetResource()->ToggleCursor(val);
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

static void MsPerGameMinuteGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetMsPerGameMinute());
}

static void MsPerGameMinuteSetter(js::PropertyContext& ctx)
{
    int32_t msPerGameMinute;
    if(!ctx.GetValue(msPerGameMinute)) return;

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

static void CamFrozenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsCamFrozen());
}

static void CamFrozenSetter(js::PropertyContext& ctx)
{
    bool state;
    if(!ctx.GetValue(state)) return;

    alt::ICore::Instance().SetCamFrozen(state);
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

static void RmlControlsGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().AreRmlControlsEnabled());
}

static void RmlControlsSetter(js::PropertyContext& ctx)
{
    bool val;
    if(!ctx.GetValue(val)) return;

    alt::ICore::Instance().ToggleRmlControls(val);
}

static void CamPosGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetCamPos());
}

static void ScreenResolutionGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().GetScreenResolution());
}

static void IsFullscreenGetter(js::PropertyContext& ctx)
{
    ctx.Return(alt::ICore::Instance().IsFullScreen());
}

static void AddGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    std::string val;
    if(!ctx.GetArg(1, val)) return;

    ctx.GetResource()->GetResource()->AddGxtText(hash, val);
}

static void RemoveGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    ctx.GetResource()->GetResource()->RemoveGxtText(hash);
}

static void GetGxtText(js::FunctionContext& ctx)
{
    uint32_t hash;
    if(!ctx.GetArgAsHash(0, hash)) return;

    ctx.Return(ctx.GetResource()->GetResource()->GetGxtText(hash));
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

static void GetCursorPos(js::FunctionContext& ctx)
{
    bool normalized = ctx.GetArg<bool>(0, false);

    ctx.Return(alt::ICore::Instance().GetCursorPosition(normalized));
}

static void SetCursorPos(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 2)) return;

    alt::Vector2f pos;
    if(!ctx.GetArg(0, pos)) return;

    bool normalized = ctx.GetArg<bool>(1, false);

    alt::ICore::Instance().SetCursorPosition(pos, normalized);
}

static void DoesConfigFlagExist(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string flag;
    if(!ctx.GetArg(0, flag)) return;

    ctx.Return(alt::ICore::Instance().DoesConfigFlagExist(flag));
}

static void DoesTextureExistInArchetype(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(2)) return;

    uint32_t modelHash;
    if(!ctx.GetArgAsHash(0, modelHash)) return;

    std::string textureName;
    if(!ctx.GetArg(1, textureName)) return;

    ctx.Return(alt::ICore::Instance().GetTextureFromDrawable(modelHash, textureName) != nullptr);
}

static void RequestIPL(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ipl;
    if(!ctx.GetArg(0, ipl)) return;

    alt::ICore::Instance().RequestIPL(ipl);
}

static void RemoveIPL(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ipl;
    if(!ctx.GetArg(0, ipl)) return;

    alt::ICore::Instance().RemoveIPL(ipl);
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

static void LoadModel(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1, 2)) return;

    uint32_t model;
    if(!ctx.GetArgAsHash(0, model)) return;

    bool async = ctx.GetArg<bool>(1, false);

    if(!async) alt::ICore::Instance().LoadModel(model);
    else
        alt::ICore::Instance().LoadModelAsync(model);
}

static void LoadYtyp(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ytyp;
    if(!ctx.GetArg(0, ytyp)) return;

    alt::ICore::Instance().LoadYtyp(ytyp);
}

static void UnloadYtyp(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string ytyp;
    if(!ctx.GetArg(0, ytyp)) return;

    alt::ICore::Instance().UnloadYtyp(ytyp);
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

static void LoadDefaultIpls(js::FunctionContext& ctx)
{
    alt::ICore::Instance().LoadDefaultIpls();
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
extern js::Namespace eventsNamespace, discordNamespace, voiceNamespace, localStorageNamespace, statsNamespace, focusDataNamespace;
static js::Module altModule("@altv/client", "@altv/shared",
    { &playerClass, &localPlayerClass, &vehicleClass, &pedClass, &networkObjectClass,
    &audioClass, &audioFilterClass, &blipClass, &textLabelClass, &checkpointClass, &webViewClass, &fontClass,
    &localPedClass, &localVehicleClass, &rmlDocumentClass, &rmlElementClass, &objectClass, &webSocketClientClass,
    &mapZoomDataClass, &virtualEntityClass, &virtualEntityGroupClass, &weaponDataClass, &handlingClass, &handlingDataClass,
    &httpClientClass, &audioOutputClass, &audioOutputAttachedClass, &audioOutputFrontendClass, &audioOutputWorldClass, &audioCategoryClass },
[](js::ModuleTemplate& module) {
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);
    module.StaticProperty("gameControlsActive", GameControlsActiveGetter, GameControlsActiveSetter);
    module.StaticProperty("cursorVisible", CursorVisibleGetter, CursorVisibleSetter);
    module.StaticProperty("locale", LocaleGetter);
    module.StaticProperty("isStreamerModeEnabled", IsStreamerModeEnabledGetter);
    module.StaticProperty("isMenuOpen", IsMenuOpenGetter);
    module.StaticProperty("isConsoleOpen", IsConsoleOpenGetter);
    module.StaticProperty("msPerGameMinute", MsPerGameMinuteGetter, MsPerGameMinuteSetter);
    module.StaticProperty("camFrozen", CamFrozenGetter, CamFrozenSetter);
    module.StaticProperty("isGameFocused", IsGameFocusedGetter);
    module.StaticProperty("fps", FpsGetter);
    module.StaticProperty("ping", PingGetter);
    module.StaticProperty("totalPacketsSent", TotalPacketsSentGetter);
    module.StaticProperty("totalPacketsLost", TotalPacketsLostGetter);
    module.StaticProperty("serverIp", ServerIpGetter);
    module.StaticProperty("serverPort", ServerPortGetter);
    module.StaticProperty("clientPath", ClientPathGetter);
    module.StaticProperty("rmlControls", RmlControlsGetter, RmlControlsSetter);
    module.StaticProperty("camPos", CamPosGetter);
    module.StaticProperty("screenResolution", ScreenResolutionGetter);
    module.StaticProperty("isFullscreen", IsFullscreenGetter);

    module.StaticLazyProperty("licenseHash", LicenseHashGetter);
    module.StaticLazyProperty("clientConfig", ClientConfigGetter);

    module.StaticFunction("addGxtText", AddGxtText);
    module.StaticFunction("removeGxtText", RemoveGxtText);
    module.StaticFunction("getGxtText", GetGxtText);
    module.StaticFunction("getKeyState", GetKeyState);
    module.StaticFunction("getCursorPos", GetCursorPos);
    module.StaticFunction("setCursorPos", SetCursorPos);
    module.StaticFunction("getConfigFlag", GetConfigFlag);
    module.StaticFunction("setConfigFlag", SetConfigFlag);
    module.StaticFunction("doesConfigFlagExist", DoesConfigFlagExist);
    module.StaticFunction("doesTextureExistInArchetype", DoesTextureExistInArchetype);
    module.StaticFunction("requestIPL", RequestIPL);
    module.StaticFunction("removeIPL", RemoveIPL);
    module.StaticFunction("beginScaleformMovieMethodMinimap", BeginScaleformMovieMethodMinimap);
    module.StaticFunction("setWeatherCycle", SetWeatherCycle);
    module.StaticFunction("setWeatherSyncActive", SetWeatherSyncActive);
    module.StaticFunction("getPermissionState", GetPermissionState);
    module.StaticFunction("takeScreenshot", TakeScreenshot);
    module.StaticFunction("setAngularVelocity", SetAngularVelocity);
    module.StaticFunction("loadModel", LoadModel);
    module.StaticFunction("loadYtyp", LoadYtyp);
    module.StaticFunction("unloadYtyp", UnloadYtyp);
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
    module.StaticFunction("loadDefaultIpls", LoadDefaultIpls);
    module.StaticFunction("getPedBonePos", GetPedBonePos);

    module.Namespace(eventsNamespace);
    module.Namespace(discordNamespace);
    module.Namespace(voiceNamespace);
    module.Namespace(localStorageNamespace);
    module.Namespace(statsNamespace);
    module.Namespace(focusDataNamespace);
    module.Namespace("WeaponObject");

    module.StaticDynamicProperty("localMeta", LocalMetaGetter);
});
