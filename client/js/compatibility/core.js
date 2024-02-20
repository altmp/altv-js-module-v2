/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

function showCursor(state) {
    alt.Cursor.visible = state;
}

function isCursorVisible() {
    return alt.Cursor.visible;
}

function getCursorPos() {
    return alt.Cursor.pos;
}

function setCursorPos(x, y) {
    alt.Cursor.pos = { x, y };
}

function setCamFrozen(state) {
    alt.Cam.frozen = state;
}

function isCamFrozen() {
    return alt.Cam.frozen;
}

function getLicenseHash() {
    return alt.licenseHash;
}

function getLocale() {
    return alt.locale;
}

function isKeyDown(key) {
    return alt.getKeyState(key).isDown;
}

function isKeyToggled(key) {
    return alt.getKeyState(key).isToggled;
}

function takeScreenshot() {
    return alt.takeScreenshot(false);
}

function takeScreenshotGameOnly() {
    return alt.takeScreenshot(true);
}

function loadModel(model) {
    return alt.Streaming.loadModel(model, false);
}

function loadModelAsync(model) {
    return alt.Streaming.loadModel(model, true);
}

function hasLocalMeta(key) {
    return alt.localMeta[key] === undefined;
}

function getLocalMeta(key) {
    return alt.localMeta[key];
}

function getCamPos() {
    return alt.Cam.pos;
}

cppBindings.registerCompatibilityExport("emitServer", alt.Events.emitServer);
cppBindings.registerCompatibilityExport("emitServerRaw", alt.Events.emitServerRaw);
cppBindings.registerCompatibilityExport("emitServerUnreliable", alt.Events.emitServerUnreliable);

cppBindings.registerCompatibilityExport("gameControlsEnabled", alt.areGameControlsActive);
cppBindings.registerCompatibilityExport("toggleGameControls", alt.setGameControlsActive);
cppBindings.registerCompatibilityExport("toggleVoiceControls", alt.Voice.toggleInput);

cppBindings.registerCompatibilityExport("showCursor", showCursor);
cppBindings.registerCompatibilityExport("isCursorVisible", isCursorVisible);
cppBindings.registerCompatibilityExport("getCursorPos", getCursorPos);
cppBindings.registerCompatibilityExport("setCursorPos", setCursorPos);

cppBindings.registerCompatibilityExport("isMenuOpen", alt.isMenuOpen);
cppBindings.registerCompatibilityExport("isConsoleOpen", alt.isConsoleOpen);

cppBindings.registerCompatibilityExport("requestIpl", alt.Streaming.requestIpl);
cppBindings.registerCompatibilityExport("removeIpl", alt.Streaming.removeIpl);

cppBindings.registerCompatibilityExport("setCamFrozen", setCamFrozen);
cppBindings.registerCompatibilityExport("isCamFrozen", isCamFrozen);

cppBindings.registerCompatibilityExport("getLicenseHash", getLicenseHash);

cppBindings.registerCompatibilityExport("addGxtText", alt.Gxt.add);
cppBindings.registerCompatibilityExport("removeGxtText", alt.Gxt.get);
cppBindings.registerCompatibilityExport("getGxtText", alt.Gxt.remove);

cppBindings.registerCompatibilityExport("setMsPerGameMinute", alt.setMsPerGameMinute);
cppBindings.registerCompatibilityExport("getMsPerGameMinute", alt.getMsPerGameMinute);

cppBindings.registerCompatibilityExport("isTextureExistInArchetype", alt.Streaming.doesTextureExistInArchetype);

cppBindings.registerCompatibilityExport("beginScaleformMovieMethodMinimap", alt.beginScaleformMovieMethodMinimap);

cppBindings.registerCompatibilityExport("getLocale", getLocale);

cppBindings.registerCompatibilityExport("setWeatherCycle", alt.setWeatherCycle);
cppBindings.registerCompatibilityExport("setWeatherSyncActive", alt.setWeatherSyncActive);

cppBindings.registerCompatibilityExport("setStat", alt.Stats.set);
cppBindings.registerCompatibilityExport("getStat", alt.Stats.get);
cppBindings.registerCompatibilityExport("resetStat", alt.Stats.reset);

cppBindings.registerCompatibilityExport("isKeyDown", isKeyDown);
cppBindings.registerCompatibilityExport("isKeyToggled", isKeyToggled);

cppBindings.registerCompatibilityExport("setConfigFlag", alt.ConfigFlag.set);
cppBindings.registerCompatibilityExport("getConfigFlag", alt.ConfigFlag.get);
cppBindings.registerCompatibilityExport("doesConfigFlagExist", alt.ConfigFlag.exists);

cppBindings.registerCompatibilityExport("setRotationVelocity", alt.setAngularVelocity);

cppBindings.registerCompatibilityExport("isInStreamerMode", alt.isStreamerModeEnabled);
cppBindings.registerCompatibilityExport("getPermissionState", alt.getPermissionState);

cppBindings.registerCompatibilityExport("takeScreenshot", takeScreenshot);
cppBindings.registerCompatibilityExport("takeScreenshotGameOnly", takeScreenshotGameOnly);

cppBindings.registerCompatibilityExport("isGameFocused", alt.isGameFocused);

cppBindings.registerCompatibilityExport("loadModel", loadModel);
cppBindings.registerCompatibilityExport("loadModelAsync", loadModelAsync);

cppBindings.registerCompatibilityExport("loadYtyp", alt.Streaming.loadYtyp);
cppBindings.registerCompatibilityExport("unloadYtyp", alt.Streaming.unloadYtyp);

cppBindings.registerCompatibilityExport("getHeadshotBase64", alt.headshotToBase64);

cppBindings.registerCompatibilityExport("setPedDlcClothes", alt.setDlcClothes);
cppBindings.registerCompatibilityExport("setPedDlcProp", alt.setDlcProps);
cppBindings.registerCompatibilityExport("clearPedProp", alt.clearProps);

cppBindings.registerCompatibilityExport("setWatermarkPosition", alt.setWatermarkPosition);

cppBindings.registerCompatibilityExport("getFps", alt.getFps);
cppBindings.registerCompatibilityExport("getPing", alt.getPing);

cppBindings.registerCompatibilityExport("getServerIp", alt.getServerIp);
cppBindings.registerCompatibilityExport("getServerPort", alt.getServerPort);

cppBindings.registerCompatibilityExport("getTotalPacketsSent", alt.getTotalPacketsSent);
cppBindings.registerCompatibilityExport("getTotalPacketsLost", alt.getTotalPacketsLost);

cppBindings.registerCompatibilityExport("hasLocalMeta", hasLocalMeta);
cppBindings.registerCompatibilityExport("getLocalMeta", getLocalMeta);

cppBindings.registerCompatibilityExport("copyToClipboard", alt.copyToClipboard);

function toggleRmlControls(state) {
    alt.setRmlControlsActive(state);
}

cppBindings.registerCompatibilityExport("toggleRmlControls", alt.setRmlControlsActive);
cppBindings.registerCompatibilityExport("rmlControlsEnabled", alt.areRmlControlsActive);
cppBindings.registerCompatibilityExport("loadRmlFont", alt.loadRmlFontFace);

cppBindings.registerCompatibilityExport("worldToScreen", alt.worldToScreen);
cppBindings.registerCompatibilityExport("screenToWorld", alt.screenToWorld);

cppBindings.registerCompatibilityExport("getCamPos", getCamPos);
cppBindings.registerCompatibilityExport("getScreenResolution", alt.getScreenResolution);

cppBindings.registerCompatibilityExport("setMinimapComponentPosition", alt.setMinimapComponentPosition);
cppBindings.registerCompatibilityExport("resetMinimapComponentPosition", alt.resetMinimapComponentPosition);
cppBindings.registerCompatibilityExport("setMinimapIsRectangle", alt.setMinimapIsRectangle);

cppBindings.registerCompatibilityExport("loadDefaultIpls", alt.Streaming.loadDefaultIpls);

cppBindings.registerCompatibilityExport("isPointOnScreen", alt.isPointOnScreen);

cppBindings.registerCompatibilityExport("getPedBonePos", alt.getPedBonePos);
cppBindings.registerCompatibilityExport("isWorker", false);

// cppBindings.registerCompatibilityExport("evalModule", alt.evalModule);
cppBindings.registerCompatibilityExport("isFullScreen", alt.isFullscreen);
