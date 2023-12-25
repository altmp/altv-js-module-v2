/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

export class Entity extends alt.Entity {
    constructor() {
        super();

        extendAltEntityClass(this, SharedEntity, WorldObject, BaseObject);
    }

    static getByScriptID(...args) {
        // NOTE (xLuxy): This method in v1 only returns WorldObject
        if (typeof super.getByScriptID == "function") {
            return super.getByScriptID(...args);
        }

        return null;
    }

    get isSpawned() {
        if (![alt.Enums.BaseObjectType.PLAYER, alt.Enums.BaseObjectType.LOCAL_PLAYER].includes(super.type)) {
            return super.isSpawned;
        }

        return super.scriptID != 0;
    }
}

copyStaticAltEntityClassProperties(alt.Entity, Entity, SharedEntity, WorldObject, BaseObject);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
