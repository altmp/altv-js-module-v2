// clang-format off
const alt = __alt;

const cppEventsMap = new Map();
const customEventsMap = new Map();

export class Event {
    static #handlers = new Map();
    static #customHandlers = new Map();

    static registerCallback(name, eventName, custom, handler)
    {
        if(typeof handler !== "function") throw new Error(`Handler for event '${name}' is not a function`);

        const typeMap = custom ? customEventsMap : cppEventsMap;
        const type = typeMap.get(eventName);
        const map = custom ? Event.#customHandlers : Event.#handlers;

        if(!map.has(type)) map.set(type, [ handler ]);
        else map.get(type).push(handler);
    }

    // eventName = value of the enum in C++
    // name = event name (e.g. `PlayerConnect` is accessible via `alt.Events.onPlayerConnect`)
    static register(eventName, name, custom = false) {
        alt.Events[`on${name}`] = Event.registerCallback.bind(undefined, name, eventName, custom);
    }

    static invoke(eventType, data, custom) {
        const map = custom ? Event.#customHandlers : Event.#handlers;
        const handlers = map.get(eventType);
        if(!handlers) return;
        for(let handler of handlers) handler(data);
    }
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
