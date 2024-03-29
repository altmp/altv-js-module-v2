/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

const { SharedBaseObject } = requireBinding("shared/compatibility/classes/sharedBaseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

requireBinding("shared/factory.js");

class VirtualEntity extends alt.VirtualEntity {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length == 3 || args.length == 4, "3 or 4 arguments expected");

        const [group, pos, streamingDistance, data] = args;

        return alt.VirtualEntity.create({
            group,
            pos,
            streamingDistance,
            data
        });
    }
}

extendClassWithProperties(VirtualEntity, null, SharedBaseObject);

alt.VirtualEntity.setFactory(VirtualEntity);

cppBindings.registerCompatibilityExport("VirtualEntity", VirtualEntity);
