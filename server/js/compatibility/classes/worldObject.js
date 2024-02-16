/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { SharedWorldObject } = requireBinding("shared/compatibility/classes/sharedWorldObject.js");
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

extendAltEntityClass(alt.WorldObject, SharedWorldObject);

cppBindings.registerCompatibilityExport("WorldObject", alt.WorldObject);
