/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

class RadiusBlip {
    constructor(x, y, z, radius) {
        return alt.RadiusBlip.create({
            pos: { x, y, z },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("RadiusBlip", RadiusBlip);
