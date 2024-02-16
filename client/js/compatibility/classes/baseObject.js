/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedBaseObject } = requireBinding("shared/compatibility/classes/sharedBaseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

extendAltEntityClass(alt.BaseObject, SharedBaseObject);

cppBindings.registerCompatibilityExport("BaseObject", alt.BaseObject);
