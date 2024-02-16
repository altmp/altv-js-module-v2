/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class AudioFilter extends alt.AudioFilter {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        return alt.AudioFilter.create({ hash: args[0] });
    }

    toString() {
        return `AudioFilter{ hash: ${this.hash} }`;
    }
}

cppBindings.registerCompatibilityExport("AudioFilter", AudioFilter);
