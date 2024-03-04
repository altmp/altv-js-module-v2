/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("shared/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");

class RadiusBlip {
    constructor(...args) {
        if (!args.length) return this;

        assert(args.length === 5, "5 arguments expected");

        const [x, y, z, radius, global] = args;

        return alt.RadiusBlip.create({
            pos: { x, y, z },
            radius,
            global
        });
    }
}

cppBindings.registerCompatibilityExport("RadiusBlip", RadiusBlip);
