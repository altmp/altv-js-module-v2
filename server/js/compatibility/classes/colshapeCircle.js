/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapeCircle extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        const [x, y, radius] = args;

        return alt.ColShapeCircle.create({
            pos: { x, y },
            radius
        });
    }
}

extendAltEntityClass(ColshapeCircle, WorldObject, BaseObject);

cppBindings.registerCompatibilityExport("ColshapeCircle", ColshapeCircle);
