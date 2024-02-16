/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

class VirtualEntityGroup extends alt.VirtualEntityGroup {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        return alt.VirtualEntityGroup.create({
            maxEntitiesInStream: args[0]
        });
    }
}

cppBindings.registerCompatibilityExport("VirtualEntityGroup", VirtualEntityGroup);
