/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class LocalObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 3 && args.length <= 7, "Minimum 3, maximum 7 arguments expected");

        const [model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance] = args;

        return alt.LocalObject.create({ model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance });
    }

    toString() {
        return `Object{ model: ${this.model}, scriptID: ${this.scriptID} }`;
    }

    static get count() {
        return alt.LocalObject.all.length;
    }

    get dynamic() {
        return this.isDynamic;
    }

    attachToEntity(...args) {
        return this.attachTo(...args);
    }
}

alt.LocalObject.setFactory(LocalObject);

cppBindings.registerCompatibilityExport("LocalObject", LocalObject);
