/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeCircle extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 3, "3 arguments expected");

        const [x, y, radius] = args;

        return alt.ColShapeCircle.create({
            pos: { x, y },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCircle", ColshapeCircle);
