/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

class ColshapeCylinder extends alt.ColShape {
    constructor(...args) {
        const [x, y, z, radius, height] = args;

        return alt.ColShapeCylinder.create({
            pos: { x, y, z },
            radius,
            height
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
