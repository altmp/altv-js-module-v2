/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("./utils/events.js")} */
const { getEventTypeFromName, getEventArgumentConverter, isCustomEvent } = requireBinding("shared/compatibility/utils/events.js");

const eventMap = new Map();

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function on(eventName, callback) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;
    const custom = isCustomEvent(eventType);

    // console.log(`[compatibility] Registering event handler for ${eventName} (${eventType} - ${custom ? "custom" : "generic"})`);

    if (!custom) {
        cppBindings.toggleEvent(eventType, true);
    }

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: false });

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

    // console.log(`[compatibility] Registering event handler for ${eventName} (${eventType} - ${custom ? "custom" : "generic"})`);

    if (!custom) {
        cppBindings.toggleEvent(eventType, true);
    }

    const handlers = eventMap.get(eventType) ?? [];
    handlers.push({ callback, eventName, once: true });

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

    const handlers = (eventMap.get(eventType) ?? []).filter((info) => info.callback !== callback && info.eventName !== eventName);

    if (handlers.length == 0) eventMap.delete(eventType);
    else eventMap.set(eventType, handlers);
}

/**
 *
 * @param {string | undefined} eventName
 */
function getEventListeners(eventName) {
    const eventType = getEventTypeFromName(eventName) ?? alt.Enums.EventType.SERVER_SCRIPT_EVENT;

    let handlers = eventMap.get(eventType);
    if (handlers) handlers = [...handlers];

    return handlers ?? [];
}

alt.Events.onEvent(async (ctx) => {
    const converter = getEventArgumentConverter(ctx.eventType, ctx.customEvent);
    const args = converter?.(ctx) ?? ctx.args;

    // alt.log(`[compatibility] Received event ${ctx.eventType} (${ctx.customEvent ? "custom" : "generic"})`);

    let handlers = eventMap.get(ctx.eventType);

    if ((handlers && ctx.eventType == alt.Enums.EventType.CLIENT_SCRIPT_EVENT) || ctx.eventType == alt.Enums.EventType.SERVER_SCRIPT_EVENT) {
        handlers = handlers.filter((handler) => handler.eventName == ctx.eventName);
    }

    if (!handlers) return;

    for (const { callback, once } of handlers) {
        let ret = callback(...args);

        if (ret instanceof Promise) ret = await ret;

        if (ret === false && ctx.isCancellable) {
            ctx.cancel();
            return;
        }

        if (once) {
            handlers.splice(handlers.indexOf(callback), 1);
            eventMap.set(ctx.eventType, handlers);
        }
    }
});

function emitClient(player, eventName, ...args) {
    if (!player instanceof alt.Player || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayers(player, eventName, ...args);
        return;
    }

    player.emit(eventName, ...args);
}

function emitClientRaw(player, eventName, ...args) {
    if (!player instanceof alt.Player || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayersRaw(player, eventName, ...args);
        return;
    }

    player.emitRaw(eventName, ...args);
}

function emitClientUnreliable(player, eventName, ...args) {
    if (!player instanceof alt.Player || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayersUnreliable(player, eventName, ...args);
        return;
    }

    player.emitUnreliable(eventName, ...args);
}

cppBindings.registerCompatibilityExport("on", on);
cppBindings.registerCompatibilityExport("once", once);
cppBindings.registerCompatibilityExport("off", off);
cppBindings.registerCompatibilityExport("getEventListeners", getEventListeners);

cppBindings.registerCompatibilityExport("emitClient", emitClient);
cppBindings.registerCompatibilityExport("emitClientRaw", emitClientRaw);
cppBindings.registerCompatibilityExport("emitClientUnreliable", emitClientUnreliable);

cppBindings.registerCompatibilityExport("emitAllClients", alt.Events.emitAllPlayers);
cppBindings.registerCompatibilityExport("emitAllClientsRaw", alt.Events.emitAllPlayersRaw);
cppBindings.registerCompatibilityExport("emitAllClientsUnreliable", alt.Events.emitAllPlayersUnreliableRaw);

// TODO (xLuxy)
// export function offClient(eventName: string, listener: (player: Player, ...args: any[]) => void): void;
// export function offClient(listener: (eventName: string, ...args: any[]) => void): void;
// export function onClient(listener: (eventName: string, player: Player, ...args: any[]) => void): void;
// export function onceClient(listener: (eventName: string, player: Player, ...args: any[]) => void): void;
