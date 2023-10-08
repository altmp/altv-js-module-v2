/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../shared/js/utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

const rpcHandlers = new Map();

/**
 *
 * @param {string} name
 * @param {Function} handler
 */
function onRpc(name, handler) {
    assertIsType(name, "string", "name has to be a string");
    assertIsType(handler, "function", "handler has to be a function");
    assert(!rpcHandlers.has(name), `Handler for rpc '${name}' already registered`);

    const rpcHandler = alt.RPC.register(name, handler);
    rpcHandlers.set(name, rpcHandler);
}

/**
 *
 * @param {string} name
 * @param {Function | undefined} handler
 */
function offRpc(name, handler) {
    assertIsType(name, "string", "name has to be a string");

    const rpcHandler = rpcHandlers.get(name);

    if (rpcHandler?.valid && (typeof handler == "function" || handler == undefined)) {
        rpcHandler.destroy();
        rpcHandlers.delete(name);
    }
}

cppBindings.registerCompatibilityExport("onRpc", onRpc);
cppBindings.registerCompatibilityExport("offRpc", offRpc);

if (alt.isClient) {
    function emitRpc(name, ...args) {
        return alt.RPC.send(name, ...args);
    }

    cppBindings.registerCompatibilityExport("emitRpc", emitRpc);
}
