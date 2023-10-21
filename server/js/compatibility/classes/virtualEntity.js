/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class VirtualEntity extends alt.VirtualEntity {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [group, pos, streamingDistance, data] = args;

        const instance = alt.VirtualEntity.create({
            group,
            pos,
            streamingDistance,
            data
        });

        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

alt.VirtualEntity.setFactory(VirtualEntity);
cppBindings.registerCompatibilityExport("VirtualEntity", VirtualEntity);
