/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { SharedVehicle } = requireBinding("shared/compatibility/classes/sharedVehicle.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class LocalVehicle extends alt.LocalVehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, SharedVehicle, Entity, WorldObject, BaseObject);
        }

        const [model, dimension, pos, rot, useStreaming, streamingDistance] = args;

        return alt.LocalVehicle.create({ model, dimension, pos, rot, useStreaming, streamingDistance });
    }
}

copyStaticAltEntityClassProperties(alt.LocalVehicle, LocalVehicle, SharedVehicle, Entity, WorldObject, BaseObject);

alt.LocalVehicle.setFactory(LocalVehicle);
cppBindings.registerCompatibilityExport("LocalVehicle", LocalVehicle);
