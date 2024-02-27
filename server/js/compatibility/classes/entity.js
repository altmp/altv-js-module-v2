/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

/** @type {typeof import("./../../../../shared/js/utils.js")} */
const { isObject } = requireBinding("shared/utils.js");

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");

class Entity {
    setSyncedMeta(key, value) {
        if (isObject(key)) {
            this.setMultipleSyncedMetaData(key);
            return;
        }

        this.syncedMeta[key] = value;
    }

    deleteSyncedMeta(key) {
        delete this.syncedMeta[key];
    }

    setStreamSyncedMeta(key, value) {
        if (isObject(key)) {
            this.setMultipleStreamSyncedMetaData(key);
            return;
        }

        this.streamSyncedMeta[key] = value;
    }

    deleteStreamSyncedMeta(key) {
        delete this.streamSyncedMeta[key];
    }
}

extendClassWithProperties(alt.Entity, null, Entity, SharedEntity);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
