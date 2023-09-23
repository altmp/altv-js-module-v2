/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.PED_DEATH, "pedDeath", ({ ped, killer, weapon }) => {
    return [ped, killer, weapon];
});

registerEventHandler(alt.Enums.EventType.PED_DAMAGE, "pedDamage", ({ ped, attacker, healthDamage, armourDamage, weapon }) => {
    return [ped, attacker, healthDamage, armourDamage, weapon];
});
