/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedBaseObject } = requireBinding("shared/compatibility/classes/sharedBaseObject.js");

export class BaseObject extends SharedBaseObject {
    //
}

cppBindings.registerCompatibilityExport("BaseObject", alt.BaseObject);
