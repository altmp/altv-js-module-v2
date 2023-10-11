/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AudioFilter extends alt.AudioFilter {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const instance = alt.AudioFilter.create({ hash: args[0] });
        return extendAltEntityClass(instance, BaseObject);
    }

    toString() {
        return `AudioFilter{ hash: ${super.hash} }`;
    }
}

alt.Factory.setAudioFilterFactory(AudioFilter);
cppBindings.registerCompatibilityExport("AudioFilter", AudioFilter);
