/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

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

    hasStreamSyncedMeta(key) {
        return this.streamSyncedMeta[key] === undefined;
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
