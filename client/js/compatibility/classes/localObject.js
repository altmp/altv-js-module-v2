/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class LocalObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance] = args;

        const instance = alt.LocalObject.create({ model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance });
        return extendAltEntityClass(instance, Entity, WorldObject, BaseObject);
    }

    toString() {
        return `Object{ model: ${super.model}, scriptID: ${super.scriptID} }`;
    }

    static get count() {
        return alt.LocalObject.all.length;
    }

    get dynamic() {
        return super.isDynamic;
    }

    attachToEntity(...args) {
        return super.attachTo(...args);
    }
}

alt.Factory.setLocalObjectFactory(LocalObject);
cppBindings.registerCompatibilityExport("LocalObject", LocalObject);
