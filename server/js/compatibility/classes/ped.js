/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Ped extends alt.Ped {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, position, rotation, streamingDistance] = args;

        return alt.Ped.create({
            model,
            pos: position,
            rot: rotation,
            streamingDistance
        });
    }
}

extendAltEntityClass(Ped, SharedPed);

cppBindings.registerCompatibilityExport("Ped", Ped);
