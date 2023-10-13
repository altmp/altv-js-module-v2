/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeCylinder extends alt.ColShape {
    constructor(...args) {
        const [x, y, z, radius, height] = args;
        const instance = alt.ColShapeCylinder.create({
            pos: { x, y, z },
            radius,
            height
        });

        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
