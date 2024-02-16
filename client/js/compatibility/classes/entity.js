/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Entity {
    get isSpawned() {
        return this.scriptID != 0;
    }
}

extendAltEntityClass(alt.Entity, Entity, SharedEntity);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
