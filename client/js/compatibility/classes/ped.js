/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";t

requireBinding("shared/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Ped {
    get streamedIn() {
        return this.isStreamedIn;
    }
}

extendAltEntityClass(alt.Ped, Ped, SharedPed);

cppBindings.registerCompatibilityExport("Ped", alt.Ped);
