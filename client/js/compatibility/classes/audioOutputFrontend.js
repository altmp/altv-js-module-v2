/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { AudioOutput } = requireBinding("client/compatibility/classes/audioOutput.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AudioOutputFrontend extends alt.AudioOutputFrontend {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [categoryHash] = args;

        const instance = alt.AudioOutputFrontend.create({ categoryHash });
        return extendAltEntityClass(instance, AudioOutput, BaseObject);
    }

    static get count() {
        return alt.AudioOutputFrontend.all.length;
    }
}

alt.Factory.setAudioOutputFrontendFactory(AudioOutputFrontend);
cppBindings.registerCompatibilityExport("AudioOutputFrontend", AudioOutputFrontend);
