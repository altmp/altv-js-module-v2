/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

class ColshapeCircle extends alt.ColShape {
    constructor(...args) {
        const [x, y, radius] = args;

        return alt.ColShapeCircle.create({
            pos: { x, y },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCircle", ColshapeCircle);
