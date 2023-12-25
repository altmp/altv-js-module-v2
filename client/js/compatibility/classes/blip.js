/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { SharedBlip } = requireBinding("shared/compatibility/classes/sharedBlip.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class Blip extends alt.Blip {
    constructor() {
        super();

        return extendAltEntityClass(this, SharedBlip, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Blip.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.Blip, SharedBlip, WorldObject, BaseObject);

alt.Blip.setFactory(Blip);
cppBindings.registerCompatibilityExport("Blip", alt.Blip);
