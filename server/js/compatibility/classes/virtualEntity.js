/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

class VirtualEntity extends alt.VirtualEntity {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [group, pos, streamingDistance, data] = args;

        return alt.VirtualEntity.create({
            group,
            pos,
            streamingDistance,
            data
        });
    }
}

alt.Factory.setVirtualEntityFactory(VirtualEntity);
cppBindings.registerCompatibilityExport("VirtualEntity", VirtualEntity);
