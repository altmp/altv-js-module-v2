/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("./utils/events.js")} */
const { getEventTypeFromName, getEventArgumentConverter, isCustomEvent } = requireBinding("shared/compatibility/utils/events.js");
requireBinding("shared/logging.js");

const eventMap = new Map();

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function on(eventName, callback) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;
    const custom = isCustomEvent(eventType);

    // alt.log(`[compatibility] Registering event handler for ${eventName} (${eventType} - ${custom ? "custom" : "generic"})`);

    if (!custom) {
        cppBindings.toggleEvent(eventType, true);
    }

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: false, custom });

    eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function onRemote(eventName, callback) {
    const eventType = alt.isServer ? alt.Enums.EventType.CLIENT_SCRIPT_EVENT : alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    // alt.log(`[compatibility] Registering event handler for ${eventName} (${eventType})`);

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: false, isRemote: true });

    eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function once(eventName, callback) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;
    const custom = isCustomEvent(eventType);

    // alt.log(`[compatibility] Registering event handler for ${eventName} (${eventType} - ${custom ? "custom" : "generic"})`);

    if (!custom) {
        cppBindings.toggleEvent(eventType, true);
    }

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: true, custom });

    eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function onceRemote(eventName, callback) {
    const eventType = alt.isServer ? alt.Enums.EventType.CLIENT_SCRIPT_EVENT : alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    // alt.log(`[compatibility] Registering event handler for ${eventName} (${eventType} - ${custom ? "custom" : "generic"})`);

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: true, isRemote: true });

    eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function off(eventName, callback) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;
    const custom = isCustomEvent(eventType);

    if (!custom) {
        cppBindings.toggleEvent(eventType, false);
    }

    const handlers = (eventMap.get(eventType) ?? []).filter((info) => !(info.callback === callback && info.eventName === eventName && info.custom === custom));

    if (handlers.length == 0) eventMap.delete(eventType);
    else eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function offRemote(eventName, callback) {
    const eventType = alt.isServer ? alt.Enums.EventType.CLIENT_SCRIPT_EVENT : alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    const handlers = (eventMap.get(eventType) ?? []).filter((info) => info.callback !== callback && info.eventName !== eventName && info.isRemote);

    if (handlers.length == 0) eventMap.delete(eventType);
    else eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string | undefined} eventName
 */
function getEventListeners(eventName) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    let handlers = (eventMap.get(eventType) ?? []).filter((info) => !info.isRemote && (typeof eventName != "string" || info.eventName == eventName));
    return handlers ?? [];
}

/**
 *
 * @param {string | undefined} eventName
 */
function getRemoteEventListeners(eventName) {
    const eventType = alt.isServer ? alt.Enums.EventType.CLIENT_SCRIPT_EVENT : alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    let handlers = (eventMap.get(eventType) ?? []).filter((info) => info.isRemote && (typeof eventName != "string" || info.eventName == eventName));
    return handlers ?? [];
}

alt.Events.onEvent(async (ctx) => {
    const converter = getEventArgumentConverter(ctx.eventType, ctx.customEvent);
    const args = converter?.(ctx) ?? ctx.args;

    // alt.log(`[compatibility] Received event ${ctx.eventType} (${ctx.customEvent ? "custom" : "generic"})`);

    let handlers = (eventMap.get(ctx.eventType) ?? []).filter((handler) => !!handler.custom == ctx.customEvent);

    if (handlers.length > 0 && (ctx.eventType == alt.Enums.EventType.CLIENT_SCRIPT_EVENT || ctx.eventType == alt.Enums.EventType.SERVER_SCRIPT_EVENT)) {
        const isRemote = alt.isServer ? ctx.eventType == alt.Enums.EventType.CLIENT_SCRIPT_EVENT : ctx.eventType == alt.Enums.EventType.SERVER_SCRIPT_EVENT;

        handlers = handlers.filter((handler) => handler.eventName == ctx.eventName && !!handler.isRemote == isRemote);
    }

    if (!handlers.length) return;

    for (const { callback, once } of handlers) {
        let ret = callback(...args);

        if (ret instanceof Promise) ret = await ret;

        if (ret === false && ctx.isCancellable) {
            ctx.cancel();
            return;
        } else if (typeof ret == "number" && ctx.eventType == alt.Enums.EventType.WEAPON_DAMAGE_EVENT) {
            ctx.setDamageValue(ret);
        }

        if (once) {
            handlers.splice(handlers.indexOf(callback), 1);
            eventMap.set(ctx.eventType, handlers);
        }
    }
});

cppBindings.registerCompatibilityExport("on", on);
cppBindings.registerCompatibilityExport("once", once);
cppBindings.registerCompatibilityExport("off", off);
cppBindings.registerCompatibilityExport("getEventListeners", getEventListeners);

const suffix = alt.isServer ? "Client" : "Server";
cppBindings.registerCompatibilityExport(`on${suffix}`, onRemote);
cppBindings.registerCompatibilityExport(`once${suffix}`, onceRemote);
cppBindings.registerCompatibilityExport(`off${suffix}`, offRemote);

cppBindings.registerCompatibilityExport("getRemoteEventListeners", getRemoteEventListeners);
