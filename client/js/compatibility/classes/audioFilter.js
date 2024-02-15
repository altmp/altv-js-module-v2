/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

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

extendAltEntityClass(AudioFilter, BaseObject);

alt.AudioFilter.setFactory(AudioFilter);
cppBindings.registerCompatibilityExport("AudioFilter", AudioFilter);
