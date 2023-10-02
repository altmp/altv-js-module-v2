/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.PED_HEAL, "pedHeal", ({ ped, newHealth, oldHealth, newArmour, oldArmour }) => {
    return [ped, oldHealth, newHealth, oldArmour, newArmour];
});
