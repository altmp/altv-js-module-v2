/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class WebSocketClient extends alt.WebSocketClient {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const instance = alt.WebSocketClient.create({ url: args[0] });
        return extendAltEntityClass(instance, BaseObject);
    }
}

alt.Factory.setWebSocketClientFactory(WebSocketClient);
cppBindings.registerCompatibilityExport("WebSocketClient", WebSocketClient);
