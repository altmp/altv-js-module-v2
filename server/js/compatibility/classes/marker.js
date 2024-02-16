/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [type, pos, color] = args;

        return alt.Marker.create({ type, pos, color });
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

cppBindings.registerCompatibilityExport("Marker", Marker);
