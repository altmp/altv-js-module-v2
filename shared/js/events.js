/** @type {typeof import("./utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

/** @type {typeof import("../../shared/js/helpers/events.js")} */
const { emitRaw } = requireBinding("shared/helpers/events.js");

export class Event {
    /** @type {Map<number, EventHandler[]>} */
    static #handlers = new Map();
    /** @type {Map<number, EventHandler[]>} */
    static #customHandlers = new Map();
    /** @type {Set<GenericEventHandler>} */
    static #genericHandlers = new Set();

    /** @type {Map<string, ScriptEventHandler[]>} */
    static #localScriptEventHandlers = new Map();
    /** @type {Map<string, ScriptEventHandler[]>} */
    static #remoteScriptEventHandlers = new Map();

    /** Warning threshold in ms */
    static #warningThreshold = 100;
    static setWarningThreshold(threshold) {
        assertIsType(threshold, "number", "Expected a number as first argument");

        Event.#warningThreshold = threshold;
    }

    static #sourceLocationFrameSkipCount = 0;
    static setSourceLocationFrameSkipCount(count) {
        assertIsType(count, "number", "Expected a number as first argument");

        Event.#sourceLocationFrameSkipCount = count;
    }

    /**
     * Gets the name of the event type enum value.
     * @param {number} type
     * @param {boolean} custom
     */
    static getEventName(type, custom) {
        const enumObj = custom ? alt.Enums.CustomEventType : alt.Enums.EventType;
        return Object.keys(enumObj).find((key) => enumObj[key] === type);
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {boolean} once
     * @param {Function} handler
     */
    static #subscribe(name, type, custom, once, handler) {
        assertIsType(handler, "function", `Handler for event '${name}' is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        const eventHandler = new EventHandler(type, handler, location, custom, once);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        if (!map.has(type)) map.set(type, [eventHandler]);
        else map.get(type).push(eventHandler);

        if (!custom) cppBindings.toggleEvent(type, true);

        return eventHandler;
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static unsubscribe(type, custom, handler) {
        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(type);
        if (!handlers) return;
        const idx = handlers.findIndex((value) => value.handler === handler);
        if (idx === -1) return;
        handlers.splice(idx, 1);

        if (!custom) cppBindings.toggleEvent(type, false);
    }

    /**
     * @param {{ eventName: string }} ctx
     * @param {boolean} local
     */
    static #handleScriptEvent(ctx, local) {
        const name = ctx.eventName;
        const handlers = local ? Event.#localScriptEventHandlers.get(name) : Event.#remoteScriptEventHandlers.get(name);
        if (!handlers) return;
        const isPlayerScriptEvent = alt.isServer && !local;

        for (let eventHandler of handlers) {
            const { handler, location, onlyOnce, eventName } = eventHandler;

            try {
                const startTime = Date.now();
                if (isPlayerScriptEvent) handler(ctx.player, ...ctx.args);
                else handler(...ctx.args);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(`[JS] Event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for script event '${name}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                }

                if (onlyOnce) eventHandler.destroy();
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking script event '${name}' handler`);
                alt.logError(e);
            }
        }
    }

    static getEventHandlers() {
        const obj = {};
        for (const [key, value] of Event.#handlers) obj[key] = value.filter((val) => val.location.fileName !== "");
        for (const [key, value] of Event.#customHandlers) obj[key] = value.filter((val) => val.location.fileName !== "");
        return obj;
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {boolean} custom
     */
    static #getEventFunc(name, type, custom, once = false) {
        const func = Event.#subscribe.bind(undefined, name, type, custom, once);
        return func;
    }

    /**
     * @param {boolean} local
     */
    static getScriptEventHandlers(local) {
        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        const obj = {};
        for (let [key, value] of map) obj[key] = value.filter((val) => val.location.fileName !== "");
        return obj;
    }

    /**
     * @param {boolean} local
     * @param {boolean?} once
     */
    static getScriptEventFunc(local, once = false) {
        const func = Event.#subscribeScriptEvent.bind(undefined, local, once);
        return func;
    }

    /**
     * @param {boolean} local
     * @param {boolean} once
     * @param {string} name
     * @param {Function} handler
     */
    static #subscribeScriptEvent(local, once, name, handler) {
        assertIsType(name, "string", `Event name is not a string`);
        assertIsType(handler, "function", `Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        const eventHandler = new ScriptEventHandler(name, local, handler, location, once);

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if (!map.has(name)) map.set(name, [eventHandler]);
        else map.get(name).push(eventHandler);

        return eventHandler;
    }

    static unsubscribeScriptEvent(local, name, handler) {
        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        const handlers = map.get(name);
        if (!handlers) return;
        const idx = handlers.findIndex((value) => value.handler === handler);
        if (idx === -1) return;
        handlers.splice(idx, 1);
    }

    /**
     * @param {number} eventType
     * @param {Record<string, any>} ctx
     * @param {boolean} custom
     */
    static #invokeGeneric(eventType, ctx, custom) {
        const handlers = Event.#genericHandlers;
        if (!handlers.size) return;

        const genericCtx = Object.freeze({
            ...ctx,
            eventType,
            customEvent: custom
        });

        for (let { handler, location } of handlers) {
            try {
                const startTime = Date.now();
                handler(genericCtx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(`[JS] Generic event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for event '${Event.getEventName(eventType, custom)}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                }
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking generic event handler`);
                alt.logError(e);
            }
        }
    }

    /**
     * @param {Function} handler
     */
    static subscribeGeneric(handler) {
        assertIsType(handler, "function", `Handler for generic event is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        const eventHandler = new GenericEventHandler(handler, location);

        Event.#genericHandlers.add(eventHandler);

        return eventHandler;
    }

    /**
     * @param {Function} handler
     */
    static unsubscribeGeneric(handler) {
        Event.#genericHandlers.forEach((value) => {
            if (value.handler === handler) Event.#genericHandlers.delete(value);
        });
    }

    /**
     * @param {number} type Event type
     * @param {string} name Event name (e.g. `PlayerConnect` is accessible via `alt.Events.onPlayerConnect`)
     * @param {string} custom alt:V built-in event or a custom JS module event
     */
    static register(type, name, custom = false) {
        alt.Events[`on${name}`] = Event.#getEventFunc(name, type, custom);
        alt.Events[`once${name}`] = Event.#getEventFunc(name, type, custom, true);
    }

    /**
     * @param {number} eventType
     * @param {Record<string, unknown>} ctx
     * @param {boolean} custom
     */
    static invoke(eventType, ctx, custom) {
        Event.#invokeGeneric(eventType, ctx, custom);
        if (eventType === alt.Enums.EventType.CLIENT_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isClient);
        else if (eventType === alt.Enums.EventType.SERVER_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isServer);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if (!handlers) return;
        for (const eventHandler of handlers) {
            const { handler, location, onlyOnce } = eventHandler;

            try {
                const startTime = Date.now();
                handler(ctx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold)
                    alt.logWarning(`[JS] Event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for event '${Event.getEventName(eventType, custom)}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                if (onlyOnce) eventHandler.destroy();
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking event handler`);
                alt.logError(e);
            }
        }
    }
}

class EventHandler {
    #eventType;
    #handler;
    #location;
    #custom;
    #once;
    #valid = true;

    constructor(eventType, handler, location, custom, once) {
        this.#eventType = eventType;
        this.#handler = handler;
        this.#location = location;
        this.#custom = custom;
        this.#once = once;
    }

    #unregister() {
        Event.unsubscribe(this.#eventType, this.#custom, this.#handler);
    }

    destroy() {
        if (!this.#valid) return;
        this.#unregister();
        this.#valid = false;
    }

    get eventType() {
        return this.#eventType;
    }
    get eventTypeName() {
        return Event.getEventName(this.#eventType, this.#custom);
    }
    get handler() {
        return this.#handler;
    }
    get location() {
        return this.#location;
    }
    get onlyOnce() {
        return this.#once;
    }
    get valid() {
        return this.#valid;
    }
}

class ScriptEventHandler extends EventHandler {
    #eventName;
    #local;

    constructor(eventName, local, handler, location, once) {
        super(ScriptEventHandler.#getEventType(local), handler, location, false, once);
        this.#eventName = eventName;
        this.#local = local;
    }

    #unregister() {
        Event.unsubscribeScriptEvent(this.#local, this.#eventName, this.handler);
    }

    get eventName() {
        return this.#eventName;
    }
    get local() {
        return this.#local;
    }
    get remote() {
        return !this.#local;
    }

    static #getEventType(local) {
        if (local && alt.isClient) return alt.Enums.EventType.CLIENT_SCRIPT_EVENT;
        else if (!local && alt.isClient) return alt.Enums.EventType.SERVER_SCRIPT_EVENT;
        else if (local && alt.isServer) return alt.Enums.EventType.SERVER_SCRIPT_EVENT;
        else if (!local && alt.isServer) return alt.Enums.EventType.CLIENT_SCRIPT_EVENT;
    }
}

class GenericEventHandler extends EventHandler {
    constructor(handler, location) {
        super(alt.Enums.EventType.ALL, handler, location, false);
    }

    #unregister() {
        Event.unsubscribeGeneric(this.handler);
    }
}

alt.Events.emitRaw = emitRaw();
alt.Events.emitUnreliableRaw = emitRaw("emitUnreliable");

alt.Events.on = Event.getScriptEventFunc(true);
alt.Events.once = Event.getScriptEventFunc(true, true);

alt.Events.onRemote = Event.getScriptEventFunc(false);
alt.Events.onceRemote = Event.getScriptEventFunc(false, true);

if (alt.isClient) {
    alt.Events.onServer = Event.getScriptEventFunc(false);
    alt.Events.onceServer = Event.getScriptEventFunc(false, true);
    alt.Events.emitServerRaw = emitRaw("emitServer");
    alt.Events.emitServerUnreliableRaw = emitRaw("emitServerUnreliable");
} else {
    alt.Events.onPlayer = Event.getScriptEventFunc(false);
    alt.Events.oncePlayer = Event.getScriptEventFunc(false, true);
    alt.Events.emitPlayersRaw = emitRaw("emitPlayers");
    alt.Events.emitPlayersUnreliableRaw = emitRaw("emitPlayersUnreliable");
    alt.Events.emitAllPlayersRaw = emitRaw("emitAllPlayers");
    alt.Events.emitAllPlayersUnreliableRaw = emitRaw("emitAllPlayersUnreliable");
}
alt.Events.onEvent = Event.subscribeGeneric;

Object.defineProperties(alt.Events, {
    listeners: { get: Event.getEventHandlers },
    localListeners: { get: Event.getScriptEventHandlers.bind(undefined, true) },
    remoteListeners: { get: Event.getScriptEventHandlers.bind(undefined, false) }
});

alt.Events.setWarningThreshold = Event.setWarningThreshold;
alt.Events.setSourceLocationFrameSkipCount = Event.setSourceLocationFrameSkipCount;

function onEvent(custom, eventType, eventData) {
    return Event.invoke(eventType, eventData, custom);
}
cppBindings.registerExport(cppBindings.BindingExport.ON_EVENT, onEvent);
