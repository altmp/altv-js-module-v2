/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class LocalPed extends alt.LocalPed {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, dimension, pos, heading, useStreaming, streamingDistance] = args;

        const instance = alt.LocalPed.create({ model, dimension, pos, heading, useStreaming, streamingDistance });
        return extendAltEntityClass(instance, SharedPed, Entity, WorldObject, BaseObject);
    }
}

alt.Factory.setLocalPedFactory(LocalPed);
cppBindings.registerCompatibilityExport("LocalPed", LocalPed);
