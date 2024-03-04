/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class AudioOutputFrontend extends alt.AudioOutputFrontend {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 0 && args.length <= 1, "Minimum 0, maximum 1 arguments expected");

        const [categoryHash] = args;

        return alt.AudioOutputFrontend.create({ categoryHash });
    }

    static get count() {
        return alt.AudioOutputFrontend.all.length;
    }
}

alt.AudioOutputFrontend.setFactory(AudioOutputFrontend);

cppBindings.registerCompatibilityExport("AudioOutputFrontend", AudioOutputFrontend);
