/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

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

cppBindings.registerCompatibilityExport("ColshapeCircle", ColshapeCircle);
