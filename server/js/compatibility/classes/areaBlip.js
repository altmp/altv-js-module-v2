/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("shared/entity.js");

class AreaBlip {
    constructor(...args) {
        if (!args.length) return this;

        assert(args.length == 6, "6 arguments expected");

        const [x, y, z, width, height, global] = args;

        return alt.AreaBlip.create({
            pos: { x, y, z },
            scale: { x: width, y: height },
            global
        });
    }
}

cppBindings.registerCompatibilityExport("AreaBlip", AreaBlip);
