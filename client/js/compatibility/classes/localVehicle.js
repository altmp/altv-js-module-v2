/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class LocalVehicle extends alt.LocalVehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 4 && args.length <= 6, "Minimum 4, maximum 6 arguments expected");

        const [model, dimension, pos, rot, useStreaming, streamingDistance] = args;

        return alt.LocalVehicle.create({ model, dimension, pos, rot, useStreaming, streamingDistance });
    }
}

alt.LocalVehicle.setFactory(LocalVehicle);

cppBindings.registerCompatibilityExport("LocalVehicle", LocalVehicle);
