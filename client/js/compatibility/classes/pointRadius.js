/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

requireBinding("client/entity.js");

class PointBlip {
    constructor(...args) {
        assert(args.length == 3, "3 arguments expected");

        return alt.PointBlip.create({ pos: { x: args[0], y: args[1], z: args[2] } });
    }
}

cppBindings.registerCompatibilityExport("PointBlip", PointBlip);
