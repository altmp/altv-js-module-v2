/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeSphere extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 4, "4 arguments expected");

        const [x, y, z, radius] = args;

        return alt.ColShapeSphere.create({
            pos: { x, y, z },
            radius
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeSphere", ColshapeSphere);
