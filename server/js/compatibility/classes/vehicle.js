/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Vehicle extends alt.Vehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, ...rest] = args;
        const pos = rest.length <= 3 ? rest[0] : { x: rest[0], y: rest[1], z: rest[2] };
        const rot = rest.length <= 3 ? rest[1] : { x: rest[3], y: rest[4], z: rest[5] };
        const streamingDistance = rest.length === 3 ? rest[2] : rest[6];

        const instance = alt.Vehicle.create({ model, pos, rot, streamingDistance });
        return extendAltEntityClass(instance, Entity);
    }
}

alt.Factory.setVehicleFactory(Vehicle);
cppBindings.registerCompatibilityExport("Vehicle", Vehicle);
