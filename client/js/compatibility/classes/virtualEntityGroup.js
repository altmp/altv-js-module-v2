/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedBaseObject } = requireBinding("shared/compatibility/classes/sharedBaseObject.js");

requireBinding("shared/factory.js");

class VirtualEntityGroup extends alt.VirtualEntityGroup {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length === 1, "1 arguments expected");

        return alt.VirtualEntityGroup.create({
            maxEntitiesInStream: args[0]
        });
    }
}

extendClassWithProperties(VirtualEntityGroup, null, SharedBaseObject);

alt.VirtualEntityGroup.setFactory(VirtualEntityGroup);

cppBindings.registerCompatibilityExport("VirtualEntityGroup", VirtualEntityGroup);
