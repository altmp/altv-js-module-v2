/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/events.js");

/**
 * A Map that stores event type mappings.
 * @type {Map<alt.Enums.EventType, { oldEventName: string, contextToArgsFunc: Function }>}
 */
const eventMap = new Map();

/**
 * A Map that stores event type mappings for custom events.
 * @type {Map<alt.Enums.CustomEventType, { oldEventName: string, contextToArgsFunc: Function }>}
 */
const customEventMap = new Map();

/**
 *
 * @param {alt.Enums.EventType} eventType
 * @param {string} oldEventName
 * @param {Function} contextToArgsFunc
 */
export function registerEventHandler(eventType, oldEventName, contextToArgsFunc, custom = false) {
    const map = custom ? customEventMap : eventMap;
    map.set(eventType, { oldEventName, contextToArgsFunc });
}

/*
alt.Events.onEvent((ctx) => {
    const map = ctx.customEvent ? customEventMap : eventMap;
    const compatHandler = map.get(ctx.eventType);
    if (!compatHandler) return;

    const args = compatHandler.contextToArgsFunc(ctx);

    const handlers = getHandlersFromOn(compatHandler.oldEventName); // imaginary function
    for (const handler of handlers) handler(...args);
});
*/

// TODO (xLuxy): Implement logic
/*
registerEventHandler(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "", ({ player, eventName, args }) => {
    if (alt.isServer) {
        return [player, eventName, ...args];
    }

    return [eventName, ...args];
});

registerEventHandler(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "", ({ eventName, args }) => {
    return [eventName, ...args];
});
*/
