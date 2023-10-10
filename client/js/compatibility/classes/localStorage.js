/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class LocalStorage {
    get(key) {
        return alt.LocalStorage.get(key);
    }

    set(key, value) {
        alt.LocalStorage.set(key, value);
    }

    delete(key) {
        alt.LocalStorage.remove(key);
    }

    deleteAll() {
        alt.LocalStorage.clear();
    }

    clear() {
        alt.LocalStorage.clear();
    }

    save() {
        alt.LocalStorage.save();
    }

    has(key) {
        return alt.LocalStorage.has(key);
    }
}

cppBindings.registerCompatibilityExport("LocalStorage", LocalStorage);
