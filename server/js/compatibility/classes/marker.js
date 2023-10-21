/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Marker extends alt.Marker {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [type, pos, color] = args;

        const instance = alt.Marker.create({ type, pos, color });
        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Marker.all.length;
    }
}

alt.Marker.setFactory(Marker);
cppBindings.registerCompatibilityExport("Marker", Marker);
