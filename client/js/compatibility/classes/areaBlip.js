/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

requireBinding("client/entity.js");

class AreaBlip {
    constructor(x, y, z, width, height) {
        assert(arguments.length === 5, "5 arguments expected");

        return alt.AreaBlip.create({
            pos: { x, y, z },
            scale: { x: width, y: height }
        });
    }
}

cppBindings.registerCompatibilityExport("AreaBlip", AreaBlip);
