/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

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

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
