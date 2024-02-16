/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class RadiusBlip {
    constructor(...args) {
        if (!args.length) return this;

        const [x, y, z, radius, global] = args;

        return alt.RadiusBlip.create({
            pos: { x, y, z },
            radius,
            global
        });
    }
}

extendAltEntityClass(RadiusBlip, SharedBlip);

cppBindings.registerCompatibilityExport("RadiusBlip", RadiusBlip);
