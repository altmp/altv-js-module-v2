/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class Object extends alt.Object {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, Entity, WorldObject, BaseObject);
        }

        const [model, pos, rot, alpha, textureVariation, lodDistance, streamingDistance] = args;

        return alt.Object.create({
            model,
            pos,
            rot,
            alpha,
            textureVariation,
            lodDistance,
            streamingDistance
        });
    }

    static get count() {
        return alt.Object.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.Object, Object, Entity, WorldObject, BaseObject);

alt.Object.setFactory(Object);
cppBindings.registerCompatibilityExport("Object", Object);
