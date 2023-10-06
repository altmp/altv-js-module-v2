/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AreaBlip {
    constructor(x, y, z, width, height, global) {
        const instance = alt.AreaBlip.create({
            pos: { x, y, z },
            scale: { x: width, y: height },
            global
        });

        return extendAltEntityClass(instance, SharedBlip, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("AreaBlip", AreaBlip);
