/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class LocalStorage {
    static get(key) {
        return alt.LocalStorage.get(key);
    }

    static set(key, value) {
        alt.LocalStorage.set(key, value);
    }

    static delete(key) {
        alt.LocalStorage.remove(key);
    }

    static deleteAll() {
        alt.LocalStorage.clear();
    }

    static clear() {
        alt.LocalStorage.clear();
    }

    static save() {
        alt.LocalStorage.save();
    }

    static has(key) {
        return alt.LocalStorage.has(key);
    }
}

cppBindings.registerCompatibilityExport("LocalStorage", LocalStorage);
