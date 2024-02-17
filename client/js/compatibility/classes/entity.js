/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");

class Entity {
    get isSpawned() {
        return this.scriptID != 0;
    }
}

extendClassWithProperties(alt.Entity, null, Entity, SharedEntity);

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
