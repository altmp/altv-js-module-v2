/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class VirtualEntityGroup extends alt.VirtualEntityGroup {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const instance = alt.VirtualEntityGroup.create({
            maxEntitiesInStream: args[0]
        });

        return extendAltEntityClass(instance, BaseObject);
    }
}

alt.VirtualEntityGroup.setFactory(VirtualEntityGroup);
cppBindings.registerCompatibilityExport("VirtualEntityGroup", VirtualEntityGroup);
