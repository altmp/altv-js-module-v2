/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class WebSocketClient extends alt.WebSocketClient {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const instance = alt.WebSocketClient.create({ url: args[0] });
        return extendAltEntityClass(instance, BaseObject);
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expected eventName to be a string, got ${typeof eventName}`);

        return super.listeners[eventName] ?? [];
    }
}

alt.WebSocketClient.setFactory(WebSocketClient);
cppBindings.registerCompatibilityExport("WebSocketClient", WebSocketClient);
