/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [type, pos, color, useStreaming, streamingDistance] = args;

        const instance = alt.Marker.create({ type, pos, color, useStreaming, streamingDistance });
        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

alt.Marker.setFactory(Marker);
cppBindings.registerCompatibilityExport("Marker", Marker);
