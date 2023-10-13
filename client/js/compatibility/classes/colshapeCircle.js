/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

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
