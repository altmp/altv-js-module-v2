/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

class ColshapeRectangle extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        const [x, y, x2, y2] = args;

        return alt.ColShapeRectangle.create({
            pos1: { x, y },
            pos2: { x: x2, y: y2 }
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeRectangle", ColshapeRectangle);
