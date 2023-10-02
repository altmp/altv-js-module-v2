/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.EXPLOSION_EVENT, "explosion", ({ source, type, pos, fx, target }) => {
    return [source, type, pos, fx, target];
});

registerEventHandler(alt.Enums.EventType.FIRE_EVENT, "fire", ({ player, fires }) => {
    return [player, fires.map((fire) => ({ pos: fire.position, weapon: fire.weaponHash }))];
});

registerEventHandler(alt.Enums.EventType.START_PROJECTILE_EVENT, "startProjectile", ({ source, startPos, direction, ammoHash, weaponHash }) => {
    return [source, startPos, direction, ammoHash, weaponHash];
});

registerEventHandler(alt.Enums.EventType.GIVE_PED_SCRIPTED_TASK, "givePedScriptedTask", ({ source, target, taskType }) => {
    return [source, target, taskType];
});
