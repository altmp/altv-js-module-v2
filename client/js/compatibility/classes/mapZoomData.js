/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class MapZoomData extends alt.MapZoomData {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        return alt.MapZoomData.get(zoomDataId[0]);
    }
}

cppBindings.registerCompatibilityExport("MapZoomData", MapZoomData);
