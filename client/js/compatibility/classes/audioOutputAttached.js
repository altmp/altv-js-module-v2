/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");
const { AudioOutput } = requireBinding("client/compatibility/classes/audioOutput.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class AudioOutputAttached extends alt.AudioOutputAttached {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [entity, categoryHash] = args;

        return alt.AudioOutputAttached.create({ entity, categoryHash });
    }

    static get count() {
        return alt.AudioOutputAttached.all.length;
    }
}

extendAltEntityClass(AudioOutputAttached, AudioOutput, BaseObject);

alt.AudioOutputAttached.setFactory(AudioOutputAttached);
cppBindings.registerCompatibilityExport("AudioOutputAttached", AudioOutputAttached);
