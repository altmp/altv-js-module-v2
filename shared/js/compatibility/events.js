/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
import * as alt from "@altv/shared";

/** @type {typeof import("./utils/events.js")} */
const { getEventTypeFromEventName } = requireBinding("shared/compatibility/utils/events.js");

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function on(eventName, callback) {
    const eventType = getEventTypeFromEventName(eventName);

    if (eventType != alt.Enums.EventType.NONE) {
        // When the eventType is not NONE we have to deal with an API event
        return;
    }

    // Otherwise we have to deal with a custom user event

    async function wrapper(ctx) {
        const callbackRet = callback(ctx);

        let processedResult = callbackRet;
        if (callbackRet instanceof Promise) {
            processedResult = await callbackRet;
        }

        if (processedResult === false && ctx.isCancellable) {
            ctx.cancel();
        }
    }

    alt.Events.on(eventName, wrapper);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function once(eventName, callback) {
    if (typeof callback != "function") throw new Error("callback is not a function");

    let removeFn;
    async function wrapper(...args) {
        const ret = callback(...args);

        if (typeof removeFn == "function") {
            removeFn();
        }
    }

    const eventHandler = alt.Events.on(eventName, wrapper);
    removeFn = eventHandler.destroy;
}

/**
 *
 * @param {string | undefined} eventName
 */
function getEventListeners(eventName) {
    const listeners = typeof eventName == "string" ? alt.Events.on.listeners[eventName] : alt.Events.on.listeners;
    return listeners ?? [];
}

cppBindings.registerCompatibilityExport("on", on);
cppBindings.registerCompatibilityExport("once", once);
cppBindings.registerCompatibilityExport("off", alt.Events.onEvent.remove);
cppBindings.registerCompatibilityExport("getEventListeners", getEventListeners);
