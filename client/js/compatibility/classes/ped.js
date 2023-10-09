/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

const { SharedPed } = requireBinding("shared/compatibility/classes/sharedPed.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

export class Ped extends alt.Ped {
    constructor() {
        super();

        extendAltEntityClass(this, SharedPed, Entity, WorldObject, BaseObject);
    }

    get streamedIn() {
        return this.isStreamedIn;
    }
}

alt.Factory.setPedFactory(Ped);
cppBindings.registerCompatibilityExport("Ped", Ped);
