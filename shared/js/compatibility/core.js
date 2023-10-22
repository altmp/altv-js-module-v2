/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/**
 *
 * @param {string} resourceName
 */
function hasResource(resourceName) {
    return alt.Resource.all.findIndex((resource) => resource.name === resourceName) != -1;
}

function getAllResources() {
    return alt.Resource.all;
}

function getVoiceConnectionState() {
    return alt.getVoiceConnectionState();
}

// properties
cppBindings.registerCompatibilityExport("defaultDimension", alt.defaultDimension);
cppBindings.registerCompatibilityExport("globalDimension", alt.globalDimension);

cppBindings.registerCompatibilityExport("resourceName", alt.Resource.current.name);
cppBindings.registerCompatibilityExport("version", alt.version);
cppBindings.registerCompatibilityExport("sdkVersion", alt.sdkVersion);
cppBindings.registerCompatibilityExport("branch", alt.branch);
cppBindings.registerCompatibilityExport("debug", alt.isDebug);

cppBindings.registerCompatibilityExport("isClient", alt.isClient);
cppBindings.registerCompatibilityExport("isServer", alt.isServer);

// methods
cppBindings.registerCompatibilityExport("hasResource", hasResource);
cppBindings.registerCompatibilityExport("getAllResources", getAllResources);

cppBindings.registerCompatibilityExport("getVoiceConnectionState", getVoiceConnectionState);

cppBindings.registerCompatibilityExport("emit", alt.Events.emit);
cppBindings.registerCompatibilityExport("emitRaw", alt.Events.emitRaw);

cppBindings.registerCompatibilityExport("log", alt.log);
cppBindings.registerCompatibilityExport("logError", alt.logError);
cppBindings.registerCompatibilityExport("logWarning", alt.logWarning);
cppBindings.registerCompatibilityExport("logDebug", alt.logDebug);

cppBindings.registerCompatibilityExport("hash", alt.hash);
cppBindings.registerCompatibilityExport("stringToSHA256", alt.sha256);

cppBindings.registerCompatibilityExport("getNetTime", alt.getNetTime);

// classes
cppBindings.registerCompatibilityExport("Vector2", alt.Vector2);
cppBindings.registerCompatibilityExport("Vector3", alt.Vector3);
cppBindings.registerCompatibilityExport("Quaternion", alt.Quaternion);
cppBindings.registerCompatibilityExport("RGBA", alt.RGBA);
