/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("shared/factory.js");

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length === 3, "3 arguments expected");

        const [type, pos, color] = args;

        return alt.Marker.create({ type, pos, color });
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

alt.Marker.setFactory(Marker);

cppBindings.registerCompatibilityExport("Marker", Marker);
