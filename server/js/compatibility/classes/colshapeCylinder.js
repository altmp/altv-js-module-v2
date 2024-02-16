/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeCylinder extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        const [x, y, z, radius, height] = args;

        return alt.ColShapeCylinder.create({
            pos: { x, y, z },
            radius,
            height
        });
    }
}

extendAltEntityClass(ColshapeCylinder, WorldObject, BaseObject);

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
