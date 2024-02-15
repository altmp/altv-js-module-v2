/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/logging.js");

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

// NOTE(xLuxy): This class is extended by other classes
export class Entity {
    get isSpawned() {
        return this.scriptID != 0;
    }
}

extendAltEntityClass(Entity, SharedEntity, WorldObject, BaseObject);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
