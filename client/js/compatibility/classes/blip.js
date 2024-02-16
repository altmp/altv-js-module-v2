/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Blip extends alt.Blip {
    static get count() {
        return alt.Blip.all.length;
    }
}

extendAltEntityClass(Blip, SharedBlip);

cppBindings.registerCompatibilityExport("Blip", Blip);
