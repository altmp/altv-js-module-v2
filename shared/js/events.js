/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

export class Event {
    /** @type {Map<number, Function[]>} */
    static #handlers = new Map();
    /** @type {Map<number, Function[]>} */
    static #customHandlers = new Map();

    /** @type {Map<string, Function[]>} */
    static #localScriptEventHandlers = new Map();
    /** @type {Map<string, Function[]>} */
    static #remoteScriptEventHandlers = new Map();

    /** Warning threshold in ms */
    static #warningThreshold = 100;
    static setWarningThreshold(threshold) {
        assert(typeof threshold === "number", "Expected a number as first argument");
        Event.#warningThreshold = threshold;
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static async #registerCallback(name, type, custom, handler) {
        assert(typeof handler === "function", `Handler for event '${name}' is not a function`);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        if (!map.has(type)) map.set(type, [handler]);
        else map.get(type).push(handler);

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
        const idx = handlers.indexOf(handler);
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

        const evCtx = {
            args: ctx.args,
        };
        if (alt.isServer && !local) evCtx.player = ctx.player;

        for (let handler of handlers) {
            try {
                const startTime = Date.now();
                handler(evCtx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(
                        `[JS] Event handler for script event '${name}' took ${duration}ms to execute (Threshold: ${
                            Event.#warningThreshold
                        }ms)`
                    );
                }
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
        return map.get(type);
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
                get: Event.#getEventHandlers.bind(undefined, type, custom),
            },
        });
        func.remove = Event.#unregisterCallback.bind(undefined, name, type, custom);
        return func;
    }

    /**
     * @param {boolean} local
     */
    static getScriptEventFunc(local) {
        const func = Event.#subscribeScriptEvent.bind(undefined, local);
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
        assert(
            typeof handler === "function",
            `Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`
        );

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if (!map.has(name)) map.set(name, [handler]);
        else map.get(name).push(handler);
    }

    static #unsubscribeScriptEvent(local, name, handler) {
        assert(typeof name === "string", `Event name is not a string`);
        assert(
            typeof handler === "function",
            `Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`
        );

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        const handlers = map.get(name);
        if (!handlers) return;
        const idx = handlers.indexOf(handler);
        if (idx === -1) return;
        handlers.splice(idx, 1);
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
    static invoke(eventType, ctx, custom) {
        Object.freeze(ctx);
        if (eventType === alt.Enums.EventType.CLIENT_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isClient);
        else if (eventType === alt.Enums.EventType.SERVER_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isServer);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if (!handlers) return;
        for (const handler of handlers) {
            try {
                const startTime = Date.now();
                handler(ctx);
                const duration = Date.now() - startTime;
                if (duration > Event.#warningThreshold) {
                    alt.logWarning(
                        `[JS] Event handler took ${duration}ms to execute (Threshold: ${Event.#warningThreshold}ms)`
                    );
                }
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
    alt.Events.onClient = Event.getScriptEventFunc(false);
}
alt.Events.setWarningThreshold = Event.setWarningThreshold;

export function onEvent(custom, eventType, eventData) {
    Event.invoke(eventType, eventData, custom);
}
