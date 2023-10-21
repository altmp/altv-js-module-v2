/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Object extends alt.Object {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, pos, rot, alpha, textureVariation, lodDistance, streamingDistance] = args;

        const instance = alt.Object.create({
            model,
            pos,
            rot,
            alpha,
            textureVariation,
            lodDistance,
            streamingDistance
        });

        return extendAltEntityClass(instance, Entity, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Object.all.length;
    }
}

alt.Object.setFactory(Object);
cppBindings.registerCompatibilityExport("Object", Object);
