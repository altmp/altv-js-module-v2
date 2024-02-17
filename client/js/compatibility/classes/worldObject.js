/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedWorldObject } = requireBinding("shared/compatibility/classes/sharedWorldObject.js");

extendClassWithProperties(alt.WorldObject, null, SharedWorldObject);

cppBindings.registerCompatibilityExport("WorldObject", alt.WorldObject);
