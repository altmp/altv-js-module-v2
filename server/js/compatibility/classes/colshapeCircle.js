/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeCircle extends alt.ColShape {
    constructor(...args) {
        const [x, y, radius] = args;
        const instance = alt.ColShapeCircle.create({
            pos: { x, y },
            radius
        });

        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("ColshapeCircle", ColshapeCircle);
