/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { AudioOutput } = requireBinding("client/compatibility/classes/audioOutput.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class AudioOutputFrontend extends alt.AudioOutputFrontend {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, AudioOutput, BaseObject);
        }

        const [categoryHash] = args;

        return alt.AudioOutputFrontend.create({ categoryHash });
    }

    static get count() {
        return alt.AudioOutputFrontend.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.AudioOutputFrontend, AudioOutputFrontend, AudioOutput, BaseObject);

alt.AudioOutputFrontend.setFactory(AudioOutputFrontend);
cppBindings.registerCompatibilityExport("AudioOutputFrontend", AudioOutputFrontend);
