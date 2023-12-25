/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedWorldObject } = requireBinding("shared/compatibility/classes/sharedWorldObject.js");

export class WorldObject extends SharedWorldObject {
    //
}

// NOTE (xLuxy): Do NOT export the Entity class from above, otherwise it will break instanceof
cppBindings.registerCompatibilityExport("WorldObject", alt.WorldObject);
