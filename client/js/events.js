requireBinding("client/events/client.js");
requireBinding("shared/events.js");

/** @type {typeof import("../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

// WebView events
addEventsToClass(alt.WebView);
alt.Events.onWebViewEvent(({ target, name, args }) => {
    onClassEvent(target, name, args);
});

// Rmlui events
addEventsToClass(alt.RmlElement);
alt.Events.onRmluiEvent(({ target, name, args }) => {
    onClassEvent(target, name, args, true);
});

// Audio events
addEventsToClass(alt.Audio);
alt.Events.onAudioEvent(({ target, name, args }) => {
    onClassEvent(target, name, args);
});

addEventsToClass(alt.WebSocketClient);
alt.Events.onWebSocketEvent(({ target, name, args }) => {
    onClassEvent(target, name, args);
});

// *** Helpers ***
function addEventsToClass(class_) {
    if (!class_) return;

    Object.defineProperties(class_.prototype, {
        listeners: {
            get: function () {
                return Object.fromEntries(this.__eventHandlers);
            }
        },
        __eventHandlers: {
            value: new Map(),
            enumerable: false,
            writable: true,
            configurable: false
        }
    });

    class_.prototype.on = function (eventName, listener) {
        assert(eventName && typeof eventName === "string", `Invalid event name: ${eventName}`);
        assert(listener && typeof listener === "function", `Invalid listener: ${listener}`);

        let eventHandlers = this.__eventHandlers.get(eventName) ?? [];
        eventHandlers.push(listener);

        this.__eventHandlers.set(eventName, eventHandlers);
    };

    class_.prototype.once = function (eventName, listener) {
        assert(eventName && typeof eventName === "string", `Invalid event name: ${eventName}`);
        assert(listener && typeof listener === "function", `Invalid listener: ${listener}`);

        const onceListener = (...args) => {
            this.off(eventName, onceListener);
            listener(...args);
        };

        let eventHandlers = this.__eventHandlers.get(eventName) ?? [];
        eventHandlers.push(onceListener);

        this.__eventHandlers.set(eventName, eventHandlers);
    };

    class_.prototype.off = function (eventName, listener) {
        assert(eventName && typeof eventName === "string", `Invalid event name: ${eventName}`);

        let eventHandlers = this.__eventHandlers.get(eventName);
        eventHandlers = eventHandlers?.filter((l) => l !== listener);

        if (eventHandlers?.length) this.__eventHandlers.set(eventName, eventHandlers);
        else this.__eventHandlers.delete(eventName);
    };
}

function onClassEvent(target, eventName, args, passArgsRaw = false) {
    const listeners = target?.__eventHandlers?.get(eventName);
    if (!listeners) return;

    for (const listener of listeners) {
        if (passArgsRaw) listener(args);
        else listener(...args);
    }
}
