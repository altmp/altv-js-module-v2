/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

class PointBlip {
    constructor(...args) {
        if (args.length == 3) return alt.PointBlip.create({ pos: { x: args[0], y: args[1], z: args[2] } });
        else return alt.PointBlip.create({ entity: args[0] });
    }
}

cppBindings.registerCompatibilityExport("PointBlip", PointBlip);
