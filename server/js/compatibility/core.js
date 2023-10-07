/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

function setSyncedMeta(key, value) {
    alt.syncedMeta[key] = value;
}

function deleteSyncedMeta(key) {
    delete alt.syncedMeta[key];
}

cppBindings.registerCompatibilityExport("setSyncedMeta", alt.setSyncedMeta);
cppBindings.registerCompatibilityExport("deleteSyncedMeta", alt.deleteSyncedMeta);

// Resource
cppBindings.registerCompatibilityExport("startResource", alt.Resource.start);
cppBindings.registerCompatibilityExport("stopResource", alt.Resource.stop);
cppBindings.registerCompatibilityExport("restartResource", alt.Resource.restart);

// Model
cppBindings.registerCompatibilityExport("getVehicleModelInfoByHash", alt.VehicleModelInfo.get);
cppBindings.registerCompatibilityExport("getPedModelInfoByHash", alt.PedModelInfo.get);
cppBindings.registerCompatibilityExport("getWeaponModelInfoByHash", alt.WeaponModelInfo.get);

// TODO (xLuxy): Missing from v2
// cppBindings.registerCompatibilityExport("getAmmoHashForWeaponHash", alt.we);

cppBindings.registerCompatibilityExport("getServerConfig", () => alt.serverConfig);

// Streaming
cppBindings.registerCompatibilityExport("getMaxStreamingPeds", () => alt.Streaming.maxStreamingPeds);
cppBindings.registerCompatibilityExport("setMaxStreamingPeds", (val) => (alt.Streaming.maxStreamingPeds = val));

cppBindings.registerCompatibilityExport("getMaxStreamingObjects", () => alt.Streaming.maxStreamingObjects);
cppBindings.registerCompatibilityExport("getMaxStreamingObjects", (val) => (alt.Streaming.maxStreamingObjects = val));

cppBindings.registerCompatibilityExport("getMaxStreamingVehicles", () => alt.Streaming.maxStreamingVehicles);
cppBindings.registerCompatibilityExport("setMaxStreamingVehicles", (val) => (alt.Streaming.maxStreamingVehicles = val));

cppBindings.registerCompatibilityExport("getStreamerThreadCount", () => alt.Streaming.streamerThreadCount);
cppBindings.registerCompatibilityExport("setStreamerThreadCount", (val) => (alt.Streaming.streamerThreadCount = val));

cppBindings.registerCompatibilityExport("getStreamingTickRate", () => alt.Streaming.streamingTickRate);
cppBindings.registerCompatibilityExport("setStreamingTickRate", (val) => (alt.Streaming.streamingTickRate = val));

cppBindings.registerCompatibilityExport("getStreamingDistance", () => alt.Streaming.streamingDistance);
cppBindings.registerCompatibilityExport("setStreamingDistance", (val) => (alt.Streaming.streamingDistance = val));

cppBindings.registerCompatibilityExport("getMigrationThreadCount", () => alt.Streaming.migrationThreadCount);
cppBindings.registerCompatibilityExport("setMigrationThreadCount", (val) => (alt.Streaming.migrationThreadCount = val));

cppBindings.registerCompatibilityExport("getSyncSendThreadCount", () => alt.Streaming.syncSendThreadCount);
cppBindings.registerCompatibilityExport("setSyncSendThreadCount", (val) => (alt.Streaming.syncSendThreadCount = val));

cppBindings.registerCompatibilityExport("getSyncReceiveThreadCount", () => alt.Streaming.syncReceiveThreadCount);
cppBindings.registerCompatibilityExport("setSyncReceiveThreadCount", (val) => (alt.Streaming.syncReceiveThreadCount = val));

cppBindings.registerCompatibilityExport("getMigrationTickRate", () => alt.Streaming.migrationTickRate);
cppBindings.registerCompatibilityExport("setMigrationTickRate", (val) => (alt.Streaming.migrationTickRate = val));

cppBindings.registerCompatibilityExport("getColShapeTickRate", () => alt.Streaming.colShapeTickRate);
cppBindings.registerCompatibilityExport("setColShapeTickRate", (val) => (alt.Streaming.colShapeTickRate = val));

cppBindings.registerCompatibilityExport("getMigrationDistance", () => alt.Streaming.migrationDistance);
cppBindings.registerCompatibilityExport("setMigrationDistance", (val) => (alt.Streaming.migrationDistance = val));
