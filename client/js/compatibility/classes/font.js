/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Font extends alt.Font {
    constructor() {
        super();

        extendAltEntityClass(this, BaseObject);
    }
}

cppBindings.registerCompatibilityExport("Font", Font);
