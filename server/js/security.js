/** @type {typeof import("../../shared/js/utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

requireBinding("server/events/player.js");

class EventProtection {
    static #enabled = false;
    static #eventHandler = null;
    static #connectHandler = null;
    static #disconnectHandler = null;
    static #timer = null;
    static #sentEventsMap = new Map();

    // Customizable
    static #ignoredPlayers = new Set();
    static #ignoredEvents = new Set();
    static #eventMaxOverrides = new Map();
    static #maxEventsPerInterval = 20;
    static #cleanupInterval = 5000;
    static #notifyCallback = null;

    static #onEvent(ctx) {
        if (ctx.customEvent || ctx.eventType !== alt.Enums.EventType.CLIENT_SCRIPT_EVENT) return;

        const player = ctx.player;
        const evName = ctx.eventName;
        if (EventProtection.#ignoredPlayers.has(player) || EventProtection.#ignoredEvents.has(evName)) return;

        /** @type {Map<string, number>} */
        let sentEvents = EventProtection.#sentEventsMap.get(player);
        if (sentEvents === undefined) {
            sentEvents = new Map();
            EventProtection.#sentEventsMap.set(player, sentEvents);
        }

        const sendCount = sentEvents.get(evName) ?? 0;
        const maxSend = EventProtection.#eventMaxOverrides.get(evName) ?? EventProtection.#maxEventsPerInterval;
        if (sendCount > maxSend) {
            if (EventProtection.#notifyCallback) EventProtection.#notifyCallback(player, evName);
            else player.kick(`Event Protection: Kicked for sending too many events.`);
        } else sentEvents.set(evName, sendCount + 1);
    }
    static #onConnect(ctx) {
        const player = ctx.player;
        EventProtection.#sentEventsMap.set(player, new Map());
    }
    static #onDisconnect(ctx) {
        const player = ctx.player;
        EventProtection.#sentEventsMap.delete(player);
    }
    static #cleanup() {
        for (const map of EventProtection.#sentEventsMap.values()) map.clear();
    }

    static #initEvents() {
        EventProtection.#eventHandler = alt.Events.onEvent(EventProtection.#onEvent);
        EventProtection.#connectHandler = alt.Events.onPlayerConnect(EventProtection.#onConnect);
        EventProtection.#disconnectHandler = alt.Events.onPlayerDisconnect(EventProtection.#onDisconnect);
    }
    static #deinitEvents() {
        EventProtection.#eventHandler.destroy();
        EventProtection.#eventHandler = null;
        EventProtection.#connectHandler.destroy();
        EventProtection.#connectHandler = null;
        EventProtection.#disconnectHandler.destroy();
        EventProtection.#disconnectHandler = null;
    }
    static #initTimer() {
        EventProtection.#timer = alt.Timers.setInterval(EventProtection.#cleanup, EventProtection.#cleanupInterval);
    }
    static #deinitTimer() {
        EventProtection.#timer.destroy();
        EventProtection.#timer = null;
    }

    static #init() {
        EventProtection.#initEvents();
        EventProtection.#initTimer();
    }
    static #deinit() {
        EventProtection.#deinitEvents();
        EventProtection.#deinitTimer();
    }

    static ignorePlayer(player) {
        assert(player instanceof alt.Player, "player has to be a Player instance");

        EventProtection.#ignoredPlayers.add(player);
    }
    static unignorePlayer(player) {
        assert(player instanceof alt.Player, "player has to be a Player instance");

        EventProtection.#ignoredPlayers.delete(player);
    }
    static ignoreEvent(event) {
        assertIsType(event, "string", "event has to be a string");

        EventProtection.#ignoredEvents.add(event);
    }
    static unignoreEvent(event) {
        assertIsType(event, "string", "event has to be a string");

        EventProtection.#ignoredEvents.delete(event);
    }
    static addCustomEventMax(event, max) {
        assertIsType(event, "string", "event has to be a string");
        assertIsType(max, "number", "max has to be a number");

        EventProtection.#eventMaxOverrides.set(event, max);
    }
    static removeCustomEventMax(event) {
        assertIsType(event, "string", "event has to be a string");

        EventProtection.#eventMaxOverrides.delete(event);
    }

    static get enabled() {
        return EventProtection.#enabled;
    }
    static set enabled(state) {
        assertIsType(state, "boolean", "state has to be a boolean");
        if (EventProtection.#enabled === state) return;
        EventProtection.#enabled = state;

        if (state) EventProtection.#init();
        else EventProtection.#deinit();
    }
    static get cleanupInterval() {
        return EventProtection.#cleanupInterval;
    }
    static set cleanupInterval(interval) {
        assertIsType(interval, "number", "interval has to be a number");
        EventProtection.#cleanupInterval = interval;

        EventProtection.#deinitTimer();
        EventProtection.#initTimer();
    }
    static get maxEventsPerInterval() {
        return EventProtection.#maxEventsPerInterval;
    }
    static set maxEventsPerInterval(max) {
        assertIsType(max, "number", "max has to be a number");

        EventProtection.#maxEventsPerInterval = max;
    }
    static get notifyCallback() {
        return EventProtection.#notifyCallback;
    }
    static set notifyCallback(callback) {
        if (callback !== null) assertIsType(callback, "function", "callback has to be a function");

        EventProtection.#notifyCallback = callback;
    }
}

alt.Security.EventProtection = EventProtection;
