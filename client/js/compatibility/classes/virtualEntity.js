/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");

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
