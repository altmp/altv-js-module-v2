/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("shared/entity.js");

class PointBlip {
    constructor(...args) {
        if (!args.length) return this;

        assert(args.length == 2 || args.length == 4, "2 or 4 arguments expected");

        let instance;
        if (args.length === 4) {
            const [x, y, z, global] = args;

            instance = alt.PointBlip.create({ pos: { x, y, z }, global });
        } else if (args.length === 2) {
            const [arg, global] = args;

            if (arg instanceof alt.Entity) instance = alt.PointBlip.create({ entity: arg, global });
            else instance = alt.PointBlip.create({ pos: arg, global });
        }

        return instance;
    }
}

cppBindings.registerCompatibilityExport("PointBlip", PointBlip);
