/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AreaBlip {
    constructor(x, y, z, width, height) {
        const instance = alt.AreaBlip.create({
            pos: { x, y, z },
            scale: { x: width, y: height }
        });

        return extendAltEntityClass(instance, SharedBlip, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("AreaBlip", AreaBlip);
