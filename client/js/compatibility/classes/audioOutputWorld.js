/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { AudioOutput } = requireBinding("client/compatibility/classes/audioOutput.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AudioOutputWorld extends alt.AudioOutputWorld {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [pos, categoryHash] = args;

        const instance = alt.AudioOutputWorld.create({ pos, categoryHash });
        return extendAltEntityClass(instance, AudioOutput, BaseObject);
    }

    static get count() {
        return alt.AudioOutputWorld.all.length;
    }
}

alt.AudioOutputWorld.setFactory(AudioOutputWorld);
cppBindings.registerCompatibilityExport("AudioOutputWorld", AudioOutputWorld);
