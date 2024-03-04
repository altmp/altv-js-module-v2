/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class AudioOutputWorld extends alt.AudioOutputWorld {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 1 && args.length <= 2, "Minimum 1, maximum 2 arguments expected");

        const [pos, categoryHash] = args;

        return alt.AudioOutputWorld.create({ pos, categoryHash });
    }

    static get count() {
        return alt.AudioOutputWorld.all.length;
    }
}

alt.AudioOutputWorld.setFactory(AudioOutputWorld);

cppBindings.registerCompatibilityExport("AudioOutputWorld", AudioOutputWorld);
