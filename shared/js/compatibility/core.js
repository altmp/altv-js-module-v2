// v1 compatibility core functions

function hash(value) {
    return alt.hash(value);
}
cppBindings.registerCompatibilityExport("hash", hash);
