/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

class Player {
    static get count() {
        return alt.Player.all.length;
    }

    get isTalking() {
        return this.talking;
    }
}

extendClassWithProperties(alt.Player, null, Player, SharedPlayer);

cppBindings.registerCompatibilityExport("Player", alt.Player);
