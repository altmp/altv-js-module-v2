/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("server/factory.js");

class Ped extends alt.Ped {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 3, "Minimum 3 arguments expected");

        const [model, position, rotation, streamingDistance] = args;

        return alt.Ped.create({
            model,
            pos: position,
            rot: rotation,
            streamingDistance
        });
    }
}

extendClassWithProperties(Ped, null, SharedPed);

alt.Ped.setFactory(Ped);

cppBindings.registerCompatibilityExport("Ped", Ped);
