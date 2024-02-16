/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

requireBinding("client/factory.js");

class WebSocketClient extends alt.WebSocketClient {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        return alt.WebSocketClient.create({ url: args[0] });
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expected eventName to be a string, got ${typeof eventName}`);

        return super.listeners[eventName] ?? [];
    }
}

alt.WebSocketClient.setFactory(WebSocketClient);

cppBindings.registerCompatibilityExport("WebSocketClient", WebSocketClient);
