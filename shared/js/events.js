/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

export class Event {
    /** @type {Map<number, ({ handler: Function, location: { fileName: string, lineNumber: number } })[]>} */
    static #handlers = new Map();
    /** @type {Map<number, ({ handler: Function, location: { fileName: string, lineNumber: number } })[]>} */
    static #customHandlers = new Map();
    /** @type {Set<({ handler: Function, location: { fileName: string, lineNumber: number } })>} */
    static #genericHandlers = new Set();

    /** @type {Map<string, ({ handler: Function, location: { fileName: string, lineNumber: number } })[]>} */
    static #localScriptEventHandlers = new Map();
    /** @type {Map<string, ({ handler: Function, location: { fileName: string, lineNumber: number } })[]>} */
    static #remoteScriptEventHandlers = new Map();

    /** Warning threshold in ms */
    static #warningThreshold = 100;
    static setWarningThreshold(threshold) {
        assert(typeof threshold === "number", "Expected a number as first argument");
        Event.#warningThreshold = threshold;
    }

    static #sourceLocationFrameSkipCount = 0;
    static setSourceLocationFrameSkipCount(count) {
        assert(typeof count === "number", "Expected a number as first argument");
        Event.#sourceLocationFrameSkipCount = count;
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static async #registerCallback(name, type, custom, handler) {
        assert(typeof handler === "function", `Handler for event '${name}' is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        const handlerObj = {
            handler,
            location
        };
        const map = custom ? Event.#customHandlers : Event.#handlers;
        if (!map.has(type)) map.set(type, [handlerObj]);
        else map.get(type).push(handlerObj);

        if (!custom) cppBindings.toggleEvent(type, true);
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static #unregisterCallback(name, type, custom, handler) {
        assert(typeof handler === "function", `Handler for event '${name}' is not a function`);

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
    static async #handleScriptEvent(ctx, local) {
        const name = ctx.eventName;
        const handlers = local ? Event.#localScriptEventHandlers.get(name) : Event.#remoteScriptEventHandlers.get(name);
        if (!handlers) return;

        for (let { handler, location } of handlers) {
            try {
                const startTime = Date.now();
                const result = handler(ctx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(`[JS] Event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for script event '${name}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                }
                if (result instanceof Promise) await result;
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking script event '${name}' handler`);
                alt.logError(e);
            }
        }
    }

    /**
     * @param {number} type
     * @param {boolean} custom
     */
    static #getEventHandlers(type, custom) {
        const map = custom ? Event.#customHandlers : Event.#handlers;
        return map.get(type).map((value) => value.handler);
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     */
    static #getEventFunc(name, type, custom) {
        const func = Event.#registerCallback.bind(undefined, name, type, custom);
        Object.defineProperties(func, {
            listeners: {
                get: Event.#getEventHandlers.bind(undefined, type, custom)
            }
        });
        func.remove = Event.#unregisterCallback.bind(undefined, name, type, custom);
        return func;
    }

    /**
     * @param {boolean} local
     */
    static #getScriptEventHandlers(local) {
        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        const obj = {};
        for (let [key, value] of map.entries()) obj[key] = value.map((value) => value.handler);
        return obj;
    }

    /**
     * @param {boolean} local
     */
    static getScriptEventFunc(local) {
        const func = Event.#subscribeScriptEvent.bind(undefined, local);
        Object.defineProperties(func, {
            listeners: {
                get: Event.#getScriptEventHandlers.bind(undefined, local)
            }
        });
        func.remove = Event.#unsubscribeScriptEvent.bind(undefined, local);
        return func;
    }

    /**
     * @param {boolean} local
     * @param {string} name
     * @param {Function} handler
     */
    static #subscribeScriptEvent(local, name, handler) {
        assert(typeof name === "string", `Event name is not a string`);
        assert(typeof handler === "function", `Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        const handlerObj = {
            handler,
            location
        };
        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if (!map.has(name)) map.set(name, [handlerObj]);
        else map.get(name).push(handlerObj);
    }

    static #unsubscribeScriptEvent(local, name, handler) {
        assert(typeof name === "string", `Event name is not a string`);
        assert(typeof handler === "function", `Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        const handlers = map.get(name);
        if (!handlers) return;
        const idx = handlers.findIndex((value) => value.handler === handler);
        if (idx === -1) return;
        handlers.splice(idx, 1);
    }

    /**
     * Gets the name of the event type enum value.
     * @param {number} type
     * @param {boolean} custom
     */
    static #getEventName(type, custom) {
        const enumObj = custom ? alt.Enums.CustomEventType : alt.Enums.EventType;
        return Object.keys(enumObj).find((key) => enumObj[key] === type);
    }

    /**
     * @param {number} eventType
     * @param {Record<string, any>} ctx
     * @param {boolean} custom
     */
    static async #invokeGeneric(eventType, ctx, custom) {
        const handlers = Event.#genericHandlers;
        if (!handlers.size) return;

        const genericCtx = Object.freeze({
            ctx,
            eventType,
            isCustom: custom
        });

        for (let { handler, location } of handlers) {
            try {
                const startTime = Date.now();
                const result = handler(genericCtx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(`[JS] Generic event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for event '${Event.#getEventName(eventType, custom)}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                }
                if (result instanceof Promise) await result;
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking generic event handler`);
                alt.logError(e);
            }
        }
    }

    static subscribeGeneric(handler) {
        assert(typeof handler === "function", `Handler for generic event is not a function`);

        const location = cppBindings.getCurrentSourceLocation(Event.#sourceLocationFrameSkipCount);
        Event.#genericHandlers.add({ handler, location });
    }
    static unsubscribeGeneric(handler) {
        assert(typeof handler === "function", `Handler for generic event is not a function`);

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
    }

    /**
     * @param {number} eventType
     * @param {Record<string, unknown>} ctx
     * @param {boolean} custom
     */
    static async invoke(eventType, ctx, custom) {
        await Event.#invokeGeneric(eventType, ctx, custom);
        if (eventType === alt.Enums.EventType.CLIENT_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isClient);
        else if (eventType === alt.Enums.EventType.SERVER_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isServer);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if (!handlers) return;
        for (const { handler, location } of handlers) {
            try {
                const startTime = Date.now();
                const result = handler(ctx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(`[JS] Event handler in resource '${cppBindings.resourceName}' (${location.fileName}:${location.lineNumber}) for event '${Event.#getEventName(eventType, custom)}' took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`);
                }
                if (result instanceof Promise) await result;
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking event handler`);
                alt.logError(e);
            }
        }
    }
}

alt.Events.on = Event.getScriptEventFunc(true);
alt.Events.onRemote = Event.getScriptEventFunc(false);
if (alt.isClient) {
    alt.Events.onServer = Event.getScriptEventFunc(false);
} else {
    alt.Events.onPlayer = Event.getScriptEventFunc(false);
}

alt.Events.onEvent = Event.subscribeGeneric;
alt.Events.onEvent.remove = Event.unsubscribeGeneric;

alt.Events.setWarningThreshold = Event.setWarningThreshold;
alt.Events.setSourceLocationFrameSkipCount = Event.setSourceLocationFrameSkipCount;

function onEvent(custom, eventType, eventData) {
    return Event.invoke(eventType, eventData, custom);
}
cppBindings.registerExport("events:onEvent", onEvent);
