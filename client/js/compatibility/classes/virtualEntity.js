/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

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

    hasStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key] !== undefined;
    }

    getStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key];
    }

    getStreamSyncedMetaKeys() {
        return Object.keys(this.streamSyncedMeta);
    }
}

alt.VirtualEntity.setFactory(VirtualEntity);

cppBindings.registerCompatibilityExport("VirtualEntity", VirtualEntity);
