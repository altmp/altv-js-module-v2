/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

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
