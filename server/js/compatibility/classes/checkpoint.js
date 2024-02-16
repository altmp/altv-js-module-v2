/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

class Checkpoint extends alt.Checkpoint {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const type = args[0];
        const pos = args.length == 8 ? args[1] : { x: args[1], y: args[2], z: args[3] };
        const nextPos = args.length == 8 ? args[2] : { x: args[4], y: args[5], z: args[6] };
        const radius = args.length == 8 ? args[3] : args[7];
        const height = args.length == 8 ? args[4] : args[8];
        const color = args.length == 8 ? args[5] : args[9];
        const iconColor = args.length == 8 ? args[6] : args[10];
        const streamingDistance = args.length == 8 ? args[7] : args[11];

        return alt.Checkpoint.create({ type, pos, nextPos, radius, height, color, iconColor, streamingDistance });
    }

    static get count() {
        return alt.Checkpoint.all.length;
    }
}

cppBindings.registerCompatibilityExport("Checkpoint", Checkpoint);
