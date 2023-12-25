/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class VirtualEntity extends alt.VirtualEntity {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, WorldObject, BaseObject);
        }

        const [group, pos, streamingDistance, data] = args;

        return alt.VirtualEntity.create({
            group,
            pos,
            streamingDistance,
            data
        });
    }
}

copyStaticAltEntityClassProperties(alt.VirtualEntity, VirtualEntity, WorldObject, BaseObject);

alt.VirtualEntity.setFactory(VirtualEntity);
cppBindings.registerCompatibilityExport("VirtualEntity", VirtualEntity);
