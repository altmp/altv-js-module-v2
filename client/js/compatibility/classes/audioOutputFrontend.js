/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class AudioOutputFrontend extends alt.AudioOutputFrontend {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [categoryHash] = args;

        return alt.AudioOutputFrontend.create({ categoryHash });
    }

    static get count() {
        return alt.AudioOutputFrontend.all.length;
    }
}

alt.AudioOutputFrontend.setFactory(AudioOutputFrontend);

cppBindings.registerCompatibilityExport("AudioOutputFrontend", AudioOutputFrontend);
