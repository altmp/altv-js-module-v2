/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapeCylinder extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 5, "5 arguments expected");

        const [x, y, z, radius, height] = args;

        return alt.ColShapeCylinder.create({
            pos: { x, y, z },
            radius,
            height
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapeCylinder", ColshapeCylinder);
