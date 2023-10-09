/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

export class SharedBaseObject {
    hasSyncedMeta(key) {
        return key in this.syncedMeta;
    }

    getSyncedMeta(key) {
        return this.syncedMeta[key];
    }

    getSyncedMetaKeys() {
        return Object.keys(this.syncedMeta);
    }

    hasMeta(key) {
        return key in this.meta;
    }

    getMeta(key) {
        return this.meta[key];
    }

    setMeta(key, value) {
        if (typeof key == "object") {
            this.setMultipleMetaData(key);
            return;
        }

        this.meta[key] = value;
    }

    deleteMeta(key) {
        delete this.meta[key];
    }

    getMetaDataKeys() {
        return Object.keys(this.meta);
    }

    getSyncedMeta(key) {
        return this.syncedMeta[key];
    }

    hasSyncedMeta(key) {
        return key in this.syncedMeta;
    }
}
