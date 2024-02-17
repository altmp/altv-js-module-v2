/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";t

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

requireBinding("shared/factory.js");

class Ped {
    get streamedIn() {
        return this.isStreamedIn;
    }
}

extendClassWithProperties(alt.Ped, null, Ped, SharedPed);

cppBindings.registerCompatibilityExport("Ped", alt.Ped);
