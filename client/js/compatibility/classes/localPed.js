/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class LocalPed extends alt.LocalPed {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, dimension, pos, heading, useStreaming, streamingDistance] = args;

        return alt.LocalPed.create({ model, dimension, pos, heading, useStreaming, streamingDistance });
    }

    get isStreamedIn() {
        return this.streamedIn;
    }
}

alt.LocalPed.setFactory(LocalPed);

cppBindings.registerCompatibilityExport("LocalPed", LocalPed);
