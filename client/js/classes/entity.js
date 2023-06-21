// Entity class extensions
/** @type {typeof import("../../../shared/js/helpers/class.js")} */
const { addGetterSetter } = requireBinding("shared/helpers/class.js");

addGetterSetter(alt.Entity, "isStreamedIn", function () {
    return this.scriptID !== 0;
});
