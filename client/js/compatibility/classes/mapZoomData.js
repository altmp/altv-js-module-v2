/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

class MapZoomData extends alt.MapZoomData {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length === 1, "1 arguments expected");

        return alt.MapZoomData.get(zoomDataId[0]);
    }
}

cppBindings.registerCompatibilityExport("MapZoomData", MapZoomData);
