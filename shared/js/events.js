// clang-format off
const serverScriptEventType = __serverScriptEventType;
const clientScriptEventType = __clientScriptEventType;
const cppEventsMap = new Map();
const customEventsMap = new Map();

export class Event {
    static #handlers = new Map();
    static #customHandlers = new Map();

    static #localScriptEventHandlers = new Map();
    static #remoteScriptEventHandlers = new Map();

    static #registerCallback(name, eventName, custom, handler) {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const typeMap = custom ? customEventsMap : cppEventsMap;
        const type = typeMap.get(eventName);
        const map = custom ? Event.#customHandlers : Event.#handlers;

        if(!map.has(type)) map.set(type, [ handler ]);
        else map.get(type).push(handler);
    }

    static #handleScriptEvent(ctx, local) {
        const name = ctx.eventName;
        const handlers = local ? Event.#localScriptEventHandlers.get(name) : Event.#remoteScriptEventHandlers.get(name);
        if(!handlers) return;

        for(let handler of handlers) handler(...ctx.args);
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
            }
        });
        return func;
    }

    static subscribeScriptEvent(local, name, handler) {
        if(typeof name !== "string") throw new Error(`Event name is not a string`);
        if(typeof handler !== "function") throw new Error(`Handler for ${local ? "local" : "remote"} script event '${name}' is not a function`);

        const map = local ? Event.#localScriptEventHandlers : Event.#remoteScriptEventHandlers;
        if(!map.has(name)) map.set(name, [ handler ]);
        else map.get(name).push(handler);
    }

    // eventName = value of the enum in C++
    // name = event name (e.g. `PlayerConnect` is accessible via `alt.Events.onPlayerConnect`)
    static register(eventName, name, custom = false) {
        alt.Events[`on${name}`] = Event.#getEventFunc(name, eventName, custom);
    }

    static invoke(eventType, ctx, custom) {
        if(eventType === serverScriptEventType) return Event.#handleScriptEvent(ctx, !alt.isClient);
        if(eventType === clientScriptEventType) return Event.#handleScriptEvent(ctx, alt.isClient);

        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if(!handlers) return;
        for(let handler of handlers) handler(ctx);
    }
}

alt.Events.on = Event.subscribeScriptEvent.bind(undefined, true);
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
