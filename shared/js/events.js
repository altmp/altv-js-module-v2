// clang-format off
requireBinding("shared/utils.js");

export class Event {
    /** @type {Map<number, Function[]>} */
    static #handlers = new Map();
    /** @type {Map<number, Function[]>} */
    static #customHandlers = new Map();

    /** @type {Map<string, Function[]>} */
    static #localScriptEventHandlers = new Map();
    /** @type {Map<string, Function[]>} */
    static #remoteScriptEventHandlers = new Map();

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static async #registerCallback(name, type, custom, handler) {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        if(!map.has(type)) map.set(type, [ handler ]);
        else map.get(type).push(handler);

        if(!custom) cppBindings.toggleEvent(type, true);
    }

    /**
     * @param {string} name
     * @param {number} type
     * @param {boolean} custom
     * @param {Function} handler
     */
    static #unregisterCallback(name, type, custom, handler) {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(type);
        if(!handlers) return;
        const idx = handlers.indexOf(handler);
        if(idx === -1) return;
        handlers.splice(idx, 1);

        if(!custom) cppBindings.toggleEvent(type, false);
    }

    /**
     * @param {{ eventName: string }} ctx
     * @param {boolean} local
     */
    static #handleScriptEvent(ctx, local) {
        const name = ctx.eventName;
        const handlers = local ? Event.#localScriptEventHandlers.get(name) : Event.#remoteScriptEventHandlers.get(name);
        if(!handlers) return;

        for(let handler of handlers) {
            if(alt.isServer && !local) handler(ctx.player, ...ctx.args);
            else handler(...ctx.args);
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
            "listeners": {
                get: Event.#getEventHandlers.bind(undefined, type, custom)
            },
        });
        func.remove = Event.#unregisterCallback.bind(undefined, name, type, custom);
        return func;
    }

    /**
     * @param {boolean} local
     * @param {string} name
     * @param {Function} handler
     */
    static subscribeScriptEvent(local, name, handler) {
        if(typeof name !== "string") throw new Error(`Event name is not a string`);
        if(typeof handler !== "function") throw new Error(`Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if(!map.has(name)) map.set(name, [ handler ]);
        else map.get(name).push(handler);
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
        if(eventType === alt.Enums.EventType.CLIENT_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isServer);
        else if(eventType === alt.Enums.EventType.SERVER_SCRIPT_EVENT) Event.#handleScriptEvent(ctx, alt.isClient);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if(!handlers) return;
        for(const handler of handlers) handler(ctx);
    }
}

alt.Events.on = Event.subscribeScriptEvent.bind(undefined, true);
alt.Events.onRemote = Event.subscribeScriptEvent.bind(undefined, false);
if(alt.isClient) {
    alt.Events.onServer = Event.subscribeScriptEvent.bind(undefined, false);
}
else {
    alt.Events.onClient = Event.subscribeScriptEvent.bind(undefined, false);
}

export function onEvent(custom, eventType, eventData) {
    Event.invoke(eventType, eventData, custom);
}
