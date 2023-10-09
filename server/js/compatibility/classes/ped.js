/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("server/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Ped extends alt.Ped {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, position, rotation, streamingDistance] = args;

        const instance = alt.Ped.create({
            model,
            pos: position,
            rot: rotation,
            streamingDistance
        });

        return extendAltEntityClass(instance, SharedPed, Entity, WorldObject, BaseObject);
    }
}

alt.Factory.setPedFactory(Ped);
cppBindings.registerCompatibilityExport("Ped", Ped);
