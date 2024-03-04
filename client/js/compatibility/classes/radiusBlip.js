/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

requireBinding("client/entity.js");

class RadiusBlip {
    constructor(...args) {
        assert(args.length === 4, "4 arguments expected");

        const [x, y, z, radius] = args;
        return alt.RadiusBlip.create({
            pos: { x, y, z },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("RadiusBlip", RadiusBlip);
