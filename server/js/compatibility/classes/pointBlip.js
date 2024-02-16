/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class PointBlip {
    constructor(...args) {
        if (!args.length) return this;

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

extendAltEntityClass(PointBlip, SharedBlip);

cppBindings.registerCompatibilityExport("PointBlip", PointBlip);
