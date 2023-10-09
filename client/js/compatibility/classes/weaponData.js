/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class WeaponData {
    constructor(weaponHash) {
        if (!weaponHash) return;

        return alt.WeaponData.get(weaponHash);
    }

    static getForHash(weaponHash) {
        return alt.WeaponData.get(weaponHash);
    }

    static get allHashes() {
        return alt.WeaponData.all.map((weaponData) => weaponData.nameHash);
    }
}

cppBindings.registerCompatibilityExport("WeaponData", WeaponData);
