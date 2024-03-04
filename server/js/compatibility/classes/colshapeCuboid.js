/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeCuboid extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 6, "6 arguments expected");

        const [x, y, z, x2, y2, z2] = args;

        return alt.ColShapeCuboid.create({
            pos1: { x, y, z },
            pos2: { x: x2, y: y2, z: z2 }
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCuboid", ColshapeCuboid);
