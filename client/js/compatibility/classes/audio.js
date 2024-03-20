/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType, assert } = requireBinding("shared/utils.js");

class Audio extends alt.Audio {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 1 && args.length <= 4, "Minimum 1, maximum 4 arguments expected");

        const [source, volume, radio, clearCache] = args;

        return alt.Audio.create({ source, volume, radio, clearCache });
    }

    static get count() {
        return alt.Audio.all.length;
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expected eventName to be a string, got ${typeof eventName}`);

        return this.listeners[eventName] ?? [];
    }

    get playing() {
        return this.isPlaying;
    }

    getOutputs() {
        return this.outputs;
    }
}

alt.Audio.setFactory(Audio);

cppBindings.registerCompatibilityExport("Audio", Audio);
