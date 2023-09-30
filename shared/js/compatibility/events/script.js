/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(
    alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE,
    "entityEnterColshape",
    ({ entity, colShape }) => {
        return [colShape, entity];
    },
    true
);

registerEventHandler(
    alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE,
    "entityLeaveColshape",
    ({ entity, colShape }) => {
        return [colShape, entity];
    },
    true
);

registerEventHandler(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "__CLIENT_SCRIPT_EVENT__", ({ player, args }) => {
    return alt.isServer ? [player, ...args] : args;
});

registerEventHandler(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "__SERVER_SCRIPT_EVENT__", ({ args }) => {
    return args;
});
