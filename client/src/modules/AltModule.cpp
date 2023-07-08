#include "Module.h"
#include "interfaces/IResource.h"

static void GameControlsActiveGetter(js::PropertyContext& ctx)
{
    ctx.Return(ctx.GetResource()->GetResource()->GameControlsActive());
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

// clang-format off
extern js::Class playerClass, localPlayerClass, vehicleClass, pedClass, networkObjectClass,
                audioClass, audioFilterClass, blipClass, textLabelClass, checkpointClass, webViewClass, fontClass,
                localPedClass, localVehicleClass, rmlDocumentClass, rmlElementClass, objectClass, webSocketClientClass,
                mapZoomDataClass, virtualEntityClass, virtualEntityGroupClass, weaponDataClass, handlingClass, handlingDataClass,
                httpClientClass, audioOutputClass, audioOutputAttachedClass, audioOutputFrontendClass, audioOutputWorldClass;
extern js::Namespace eventsNamespace, discordNamespace, voiceNamespace, localStorageNamespace, statsNamespace;
static js::Module altModule("@altv/client", "@altv/shared",
    { &playerClass, &localPlayerClass, &vehicleClass, &pedClass, &networkObjectClass,
    &audioClass, &audioFilterClass, &blipClass, &textLabelClass, &checkpointClass, &webViewClass, &fontClass,
    &localPedClass, &localVehicleClass, &rmlDocumentClass, &rmlElementClass, &objectClass, &webSocketClientClass,
    &mapZoomDataClass, &virtualEntityClass, &virtualEntityGroupClass, &weaponDataClass, &handlingClass, &handlingDataClass,
    &httpClientClass, &audioOutputClass, &audioOutputAttachedClass, &audioOutputFrontendClass, &audioOutputWorldClass  },
[](js::ModuleTemplate& module) {
    module.StaticProperty("isClient", true);
    module.StaticProperty("isServer", false);
    module.StaticProperty("gameControlsActive", GameControlsActiveGetter, GameControlsActiveSetter);
    module.StaticProperty("cursorVisible", CursorVisibleGetter, CursorVisibleSetter);

    module.StaticFunction("addGxtText", AddGxtText);
    module.StaticFunction("removeGxtText", RemoveGxtText);
    module.StaticFunction("getGxtText", GetGxtText);

    module.Namespace(eventsNamespace);
    module.Namespace(discordNamespace);
    module.Namespace(voiceNamespace);
    module.Namespace(localStorageNamespace);
    module.Namespace(statsNamespace);
    module.Namespace("WeaponObject");

});
