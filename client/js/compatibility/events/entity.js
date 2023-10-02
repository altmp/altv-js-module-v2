/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.GAME_ENTITY_CREATE, "gameEntityCreate", ({ entity }) => {
    return [entity];
});

registerEventHandler(alt.Enums.EventType.GAME_ENTITY_DESTROY, "gameEntityDestroy", ({ entity }) => {
    return [entity];
});

registerEventHandler(alt.Enums.EventType.TASK_CHANGE, "taskChange", ({ oldTask, newTask }) => {
    return [oldTask, newTask];
});

registerEventHandler(alt.Enums.EventType.ENTITY_HIT_ENTITY, "entityHitEntity", ({ target, damager, weapon }) => {
    return [damager, target, weapon];
});
