/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

export class Player extends alt.Player {
    constructor() {
        super();

        extendAltEntityClass(this, SharedPlayer, Entity, WorldObject, BaseObject);
    }

    static get count() {
        return alt.Player.all.length;
    }
}

copyStaticAltEntityClassProperties(alt.Player, Player, SharedPlayer, Entity, WorldObject, BaseObject);

alt.Player.setFactory(Player);
cppBindings.registerCompatibilityExport("Player", Player);
