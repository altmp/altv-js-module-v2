/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

class Entity extends alt.Entity {
    setMeta(key, value) {
        super.meta[key] = value;
    }

    deleteMeta(key) {
        delete super.meta[key];
    }

    getMeta(key) {
        return super.meta[key];
    }

    hasMeta(key) {
        return key in super.meta;
    }

    setSyncedMeta(key, value) {
        super.syncedMeta[key] = value;
    }

    deleteSyncedMeta(key) {
        delete super.syncedMeta[key];
    }

    getSyncedMeta(key) {
        return super.syncedMeta[key];
    }

    hasSyncedMeta(key) {
        return key in super.syncedMeta;
    }

    setStreamSyncedMeta(key, value) {
        super.streamSyncedMeta[key] = value;
    }

    deleteStreamSyncedMeta(key) {
        delete super.streamSyncedMeta[key];
    }

    getStreamSyncedMeta(key) {
        return super.streamSyncedMeta[key];
    }

    hasStreamSyncedMeta(key) {
        return key in super.streamSyncedMeta;
    }
}

cppBindings.registerCompatibilityExport("Entity", Entity);
