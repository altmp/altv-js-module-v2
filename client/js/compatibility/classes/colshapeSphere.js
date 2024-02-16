/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class ColshapeSphere extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        const [x, y, z, radius] = args;

        return alt.ColShapeSphere.create({
            pos: { x, y, z },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeSphere", ColshapeSphere);
