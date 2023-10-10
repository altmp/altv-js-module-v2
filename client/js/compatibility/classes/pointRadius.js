/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class PointBlip {
    constructor(...args) {
        let instance;
        if (args.length == 3) instance = alt.PointBlip.create({ pos: { x: args[0], y: args[1], z: args[2] } });
        else instance = alt.PointBlip.create({ entity: args[0] });

        return extendAltEntityClass(instance, SharedBlip, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("PointBlip", PointBlip);
