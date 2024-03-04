/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class ColshapePolygon extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        assert(args.length === 3, "3 arguments expected");

        const [minZ, maxZ, points] = args;

        return alt.ColShapePolygon.create({
            minZ,
            maxZ,
            points
        });
    }
}

cppBindings.registerCompatibilityExport("ColshapePolygon", ColshapePolygon);
