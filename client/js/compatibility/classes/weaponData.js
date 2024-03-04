/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsOneOfType } = requireBinding("shared/utils.js");

class WeaponData {
    constructor(weaponHash) {
        assertIsOneOfType(weaponHash, ["string", "number"], "1 arguments expected");

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
