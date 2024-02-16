/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Entity {
    setSyncedMeta(_key, _value) {
        throw new Error("Not implemented in v2 Module - Use streamSyncedMeta instead");
    }

    deleteSyncedMeta(key) {
        throw new Error("Not implemented in v2 Module - Use streamSyncedMeta instead");
    }

    setStreamSyncedMeta(key, value) {
        if (typeof key == "object") {
            this.setMultipleStreamSyncedMetaData(key);
            return;
        }

        this.streamSyncedMeta[key] = value;
    }

    deleteStreamSyncedMeta(key) {
        delete this.streamSyncedMeta[key];
    }
}

extendAltEntityClass(alt.Entity, Entity, SharedEntity);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
