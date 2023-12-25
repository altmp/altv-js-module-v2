/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class Object extends alt.Object {
    constructor() {
        super();

        extendAltEntityClass(this, Entity, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Object.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.Object, Object, Entity, WorldObject, BaseObject);

alt.Object.setFactory(Object);
cppBindings.registerCompatibilityExport("Object", Object);
