/// <reference path="../../../types/shared/index.d.ts" />

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

requireBinding("shared/classes/vector.js");

class VectorExtension {
    normalize() {
        return this.normalized;
    }
}

extendClassWithProperties(alt.Vector2, null, VectorExtension);
extendClassWithProperties(alt.Vector3, null, VectorExtension);

cppBindings.registerCompatibilityExport("Vector2", alt.Vector2);
cppBindings.registerCompatibilityExport("Vector3", alt.Vector3);
