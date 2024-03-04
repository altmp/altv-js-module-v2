/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class AudioOutputAttached extends alt.AudioOutputAttached {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 1 && args.length <= 2, "Minimum 1, maximum 2 arguments expected");

        const [entity, categoryHash] = args;

        return alt.AudioOutputAttached.create({ entity, categoryHash });
    }

    static get count() {
        return alt.AudioOutputAttached.all.length;
    }
}

alt.AudioOutputAttached.setFactory(AudioOutputAttached);

cppBindings.registerCompatibilityExport("AudioOutputAttached", AudioOutputAttached);
