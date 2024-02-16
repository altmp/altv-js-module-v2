/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class AudioOutputWorld extends alt.AudioOutputWorld {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [pos, categoryHash] = args;

        return alt.AudioOutputWorld.create({ pos, categoryHash });
    }

    static get count() {
        return alt.AudioOutputWorld.all.length;
    }
}

alt.AudioOutputWorld.setFactory(AudioOutputWorld);

cppBindings.registerCompatibilityExport("AudioOutputWorld", AudioOutputWorld);
