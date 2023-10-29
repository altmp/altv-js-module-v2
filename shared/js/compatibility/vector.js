/// <reference path="../../../types/shared/index.d.ts" />

requireBinding("shared/classes/vector.js");

class Vector3 extends alt.Vector3 {
    normalize() {
        return this.normalized;
    }
}

class Vector2 extends alt.Vector2 {
    normalize() {
        return this.normalized;
    }
}

cppBindings.registerCompatibilityExport("Vector3", Vector3);
cppBindings.registerCompatibilityExport("Vector2", Vector2);
