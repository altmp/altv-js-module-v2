/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeRectangle extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 4, "4 arguments expected");

        const [x, y, x2, y2] = args;

        return alt.ColShapeRectangle.create({
            pos1: { x, y },
            pos2: { x: x2, y: y2 }
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeRectangle", ColshapeRectangle);
