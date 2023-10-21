/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

const { Player } = requireBinding("client/compatibility/classes/entity.js");
const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class LocalPlayer extends alt.LocalPlayer {
    constructor() {
        super();

        extendAltEntityClass(this, Player, SharedPlayer, Entity, WorldObject, BaseObject);
    }
}

alt.Factory.setLocalPlayerFactory(LocalPlayer);
cppBindings.registerCompatibilityExport("LocalPlayer", LocalPlayer);
