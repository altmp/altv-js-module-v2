/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";t

requireBinding("shared/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Ped extends alt.Ped {
    get streamedIn() {
        return this.isStreamedIn;
    }
}

extendAltEntityClass(Ped, SharedPed);

alt.Ped.setFactory(Ped);

cppBindings.registerCompatibilityExport("Ped", Ped);
