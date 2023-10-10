/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedEntity } = requireBinding("shared/compatibility/classes/sharedEntity.js");

export class Entity extends SharedEntity {
    //
}

cppBindings.registerCompatibilityExport("Entity", alt.Entity);
