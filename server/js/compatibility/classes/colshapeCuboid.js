/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeCuboid extends alt.ColShape {
    constructor(...args) {
        const [x, y, z, x2, y2, z2] = args;
        const instance = alt.ColShapeCuboid.create({
            pos1: { x, y, z },
            pos2: { x: x2, y: y2, z: z2 }
        });

        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("ColshapeCuboid", ColshapeCuboid);
