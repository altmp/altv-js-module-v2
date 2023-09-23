/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE, "entityEnterColshape", ({ entity, colShape }) => {
    return [colShape, entity];
});

registerEventHandler(alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE, "entityLeaveColshape", ({ entity, colShape }) => {
    return [colShape, entity];
});

// TODO (xLuxy): Implement this properly
// NOTE (xLuxy): alt.onClient / alt.onServer - player is only available on server
registerEventHandler(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "", ({ player, eventName, args }) => {
    return [player, eventName, ...args];
});

// TODO (xLuxy): Implement this properly
// NOTE (xLuxy): alt.on / alt.once
registerEventHandler(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "", ({ eventName, args }) => {
    return [eventName, ...args];
});
