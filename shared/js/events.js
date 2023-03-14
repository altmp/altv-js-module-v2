// clang-format off
requireBinding("shared/utils.js");

const serverScriptEventType = __serverScriptEventType;
const clientScriptEventType = __clientScriptEventType;
const cppEventsMap = new Map();
const customEventsMap = new Map();

export class Event {
    /** @type {Map<number, Function[]>} */
    static #handlers = new Map();
    /** @type {Map<number, Function[]>} */
    static #customHandlers = new Map();

    /** @type {Map<string, Function[]>} */
    static #localScriptEventHandlers = new Map();
    /** @type {Map<string, Function[]>} */
    static #remoteScriptEventHandlers = new Map();

    static async #registerCallback(name, eventName, custom, handler) {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const typeMap = custom ? customEventsMap : cppEventsMap;
        if(typeMap.size === 0) await alt.Utils.waitForNextTick(); // Needed to ensure that the event types are registered

        const type = typeMap.get(eventName);
        const map = custom ? Event.#customHandlers : Event.#handlers;

        if(!map.has(type)) map.set(type, [ handler ]);
        else map.get(type).push(handler);
    }

    static #unregisterCallback(name, eventName, custom, handler) {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const typeMap = custom ? customEventsMap : cppEventsMap;
        const type = typeMap.get(eventName);
        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(type);
        if(!handlers) return;
        const idx = handlers.indexOf(handler);
        if(idx === -1) return;
        handlers.splice(idx, 1);
    }

    static #handleScriptEvent(ctx, local) {
        const name = ctx.eventName;
        const handlers = local ? Event.#localScriptEventHandlers.get(name) : Event.#remoteScriptEventHandlers.get(name);
        if(!handlers) return;

        for(let handler of handlers) {
            if(alt.isServer && !local) handler(ctx.player, ...ctx.args);
            else handler(...ctx.args);
        }
    }

    static #getEventHandlers(name, custom) {
        const typeMap = custom ? customEventsMap : cppEventsMap;
        const type = typeMap.get(name);
        const map = custom ? Event.#customHandlers : Event.#handlers;
        return map.get(type);
    }

    static #getEventFunc(name, eventName, custom) {
        const func = Event.#registerCallback.bind(undefined, name, eventName, custom);
        Object.defineProperties(func, {
            "listeners": {
                get: Event.#getEventHandlers.bind(undefined, eventName, custom)
            },
        });
        func.remove = Event.#unregisterCallback.bind(undefined, name, eventName, custom);
        return func;
    }

    static subscribeScriptEvent(local, name, handler) {
        if(typeof name !== "string") throw new Error(`Event name is not a string`);
        if(typeof handler !== "function") throw new Error(`Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if(!map.has(name)) map.set(name, [ handler ]);
        else map.get(name).push(handler);
    }

    /**
     * @param {string} eventName Name of the event enum value in C++
     * @param {string} name Event name (e.g. `PlayerConnect` is accessible via `alt.Events.onPlayerConnect`)
     * @param {string} custom alt:V built-in event or a custom JS module event
     */
    static register(eventName, name, custom = false) {
        alt.Events[`on${name}`] = Event.#getEventFunc(name, eventName, custom);
    }

    static invoke(eventType, ctx, custom) {
        if(eventType === serverScriptEventType) Event.#handleScriptEvent(ctx, alt.isServer);
        else if(eventType === clientScriptEventType) Event.#handleScriptEvent(ctx, alt.isClient);

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

export function setEvents(cppEvents, customEvents) {
    for (const event in cppEvents) {
        cppEventsMap.set(cppEvents[event], parseInt(event));
    }

    for (const event in customEvents) {
        customEventsMap.set(customEvents[event], parseInt(event));
    }
}

export function onEvent(custom, eventType, eventData) {
    Event.invoke(eventType, eventData, custom);
}
