/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeCylinder extends alt.ColShape {
    constructor(...args) {
        const [x, y, z, radius, height] = args;

        assert(args.length === 5, "5 arguments expected");

        return alt.ColShapeCylinder.create({
            pos: { x, y, z },
            radius,
            height
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
