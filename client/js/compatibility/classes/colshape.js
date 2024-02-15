/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Colshape extends alt.ColShape {
    //
}

extendAltEntityClass(Colshape, WorldObject, BaseObject);

alt.ColShape.setFactory(Colshape);
cppBindings.registerCompatibilityExport("Colshape", Colshape);
