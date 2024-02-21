/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("./../../../../shared/js/utils.js")} */
const { isObject } = requireBinding("shared/utils.js");

export class SharedBaseObject {
    hasMeta(key) {
        return this.meta[key] !== undefined;
    }

    getMeta(key) {
        return this.meta[key];
    }

    setMeta(key, value) {
        if (isObject(key)) {
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
        return this.syncedMeta[key] !== undefined;
    }

    getSyncedMetaKeys() {
        return Object.keys(this.syncedMeta);
    }
}
