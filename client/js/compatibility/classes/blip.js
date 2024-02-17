/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");

requireBinding("shared/factory.js");

class Blip extends alt.Blip {
    static get count() {
        return alt.Blip.all.length;
    }
}

extendClassWithProperties(Blip, null, SharedBlip);

alt.Blip.setFactory(Blip);

cppBindings.registerCompatibilityExport("Blip", Blip);
