/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Player {
    static get count() {
        return alt.Player.all.length;
    }
}

extendAltEntityClass(alt.Player, Player, SharedPlayer);

cppBindings.registerCompatibilityExport("Player", alt.Player);
