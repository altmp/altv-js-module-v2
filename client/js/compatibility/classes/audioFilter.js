/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class AudioFilter extends alt.AudioFilter {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length === 1, "1 arguments expected");

        return alt.AudioFilter.create({ hash: args[0] });
    }

    toString() {
        return `AudioFilter{ hash: ${this.hash} }`;
    }
}

alt.AudioFilter.setFactory(AudioFilter);

cppBindings.registerCompatibilityExport("AudioFilter", AudioFilter);
