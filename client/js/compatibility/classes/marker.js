/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, WorldObject, BaseObject);
        }

        const [type, pos, color, useStreaming, streamingDistance] = args;

        return alt.Marker.create({ type, pos, color, useStreaming, streamingDistance });
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.Marker, Marker, WorldObject, BaseObject);

alt.Marker.setFactory(Marker);
cppBindings.registerCompatibilityExport("Marker", Marker);
