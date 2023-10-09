/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class LocalStorage extends alt.LocalStorage {
    static delete(key) {
        alt.LocalStorage.remove(key);
    }

    static deleteAll() {
        alt.LocalStorage.clear();
    }
}

cppBindings.registerCompatibilityExport("LocalStorage", LocalStorage);
