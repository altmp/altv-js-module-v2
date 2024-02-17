/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

class _Object {
    static get count() {
        return alt.Object.all.length;
    }
}

extendClassWithProperties(alt.Object, null, _Object);

cppBindings.registerCompatibilityExport("Object", alt.Object);
