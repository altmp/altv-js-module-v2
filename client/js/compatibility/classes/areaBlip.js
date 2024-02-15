/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

class AreaBlip {
    constructor(x, y, z, width, height) {
        return alt.AreaBlip.create({
            pos: { x, y, z },
            scale: { x: width, y: height }
        });
    }
}

cppBindings.registerCompatibilityExport("AreaBlip", AreaBlip);
