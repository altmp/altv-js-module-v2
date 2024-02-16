/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [type, pos, color, useStreaming, streamingDistance] = args;

        return alt.Marker.create({ type, pos, color, useStreaming, streamingDistance });
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

cppBindings.registerCompatibilityExport("Marker", Marker);
