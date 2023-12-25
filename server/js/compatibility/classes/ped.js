/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("server/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class Ped extends alt.Ped {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, SharedPed, Entity, WorldObject, BaseObject);
        }

        const [model, position, rotation, streamingDistance] = args;

        return alt.Ped.create({
            model,
            pos: position,
            rot: rotation,
            streamingDistance
        });
    }
}

copyStaticAltEntityClassProperties(alt.Ped, Ped, SharedPed, Entity, WorldObject, BaseObject);

alt.Ped.setFactory(Ped);
cppBindings.registerCompatibilityExport("Ped", Ped);
