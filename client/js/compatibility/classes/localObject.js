/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class LocalObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, Entity, WorldObject, BaseObject);
        }

        const [model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance] = args;

        return alt.LocalObject.create({ model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance });
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

copyStaticAltEntityClassProperties(alt.LocalObject, LocalObject, Entity, WorldObject, BaseObject);

alt.LocalObject.setFactory(LocalObject);
cppBindings.registerCompatibilityExport("LocalObject", LocalObject);
