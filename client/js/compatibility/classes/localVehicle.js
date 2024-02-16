/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class LocalVehicle extends alt.LocalVehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, dimension, pos, rot, useStreaming, streamingDistance] = args;

        return alt.LocalVehicle.create({ model, dimension, pos, rot, useStreaming, streamingDistance });
    }
}

alt.LocalVehicle.setFactory(LocalVehicle);

cppBindings.registerCompatibilityExport("LocalVehicle", LocalVehicle);
