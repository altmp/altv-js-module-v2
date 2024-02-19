/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

class Checkpoint extends alt.Checkpoint {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const type = args[0];
        const pos = args.length == 6 ? args[1] : { x: args[1], y: args[2], z: args[3] };
        const radius = args.length == 6 ? args[2] : args[4];
        const height = args.length == 6 ? args[3] : args[5];
        const color = args.length == 6 ? args[4] : { r: args[6], g: args[7], b: args[8], a: args[9] };
        const streamingDistance = args.length == 6 ? args[5] : args[10];

        return alt.Checkpoint.create({ type, pos, radius, height, color, streamingDistance });
    }

    static get count() {
        return alt.Checkpoint.all.length;
    }
}

alt.Checkpoint.setFactory(Checkpoint);

cppBindings.registerCompatibilityExport("Checkpoint", Checkpoint);
