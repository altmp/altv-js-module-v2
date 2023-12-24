/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class VirtualEntityGroup extends alt.VirtualEntityGroup {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, BaseObject);
        }

        const instance = alt.VirtualEntityGroup.create({
            maxEntitiesInStream: args[0]
        });

        return extendAltEntityClass(instance, BaseObject);
    }
}

copyStaticAltEntityClassProperties(alt.VirtualEntityGroup, VirtualEntityGroup, BaseObject);

alt.VirtualEntityGroup.setFactory(VirtualEntityGroup);
cppBindings.registerCompatibilityExport("VirtualEntityGroup", VirtualEntityGroup);
