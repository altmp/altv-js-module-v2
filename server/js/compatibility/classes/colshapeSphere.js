/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeSphere extends alt.ColShape {
    constructor(...args) {
        const [x, y, z, radius] = args;

        const instance = alt.ColShapeSphere.create({
            pos: { x, y, z },
            radius
        });

        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("ColshapeSphere", ColshapeSphere);
