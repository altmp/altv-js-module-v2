requireBinding("shared/classes/vector.js");

class Vector3 extends alt.Vector3 {
    normalize() {
        return this.normalized;
    }
}

cppBindings.registerCompatibilityExport("Vector3", Vector3);
