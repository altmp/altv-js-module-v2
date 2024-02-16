/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

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

cppBindings.registerCompatibilityExport("AudioOutputAttached", AudioOutputAttached);
