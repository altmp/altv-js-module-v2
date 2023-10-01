/** @type {typeof import("./utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

/**
 * @type {Map<string, RPCHandler>}
 */
const rpcHandlersMap = new Map();

class RPCHandler {
    #name;
    #handler;
    #valid = true;

    constructor(name, handler) {
        this.#name = name;
        this.#handler = handler;
    }

    destroy() {
        if (!this.#valid) return;
        this.#valid = false;
        rpcHandlersMap.delete(this.#name);
    }

    get name() {
        return this.#name;
    }
    get handler() {
        return this.#handler;
    }
    get valid() {
        return this.#valid;
    }
}

alt.RPC.register = function (rpcName, handler) {
    assertIsType(rpcName, "string", "rpcName has to be a string");
    assertIsType(handler, "function", "handler has to be a function");
    assert(!rpcHandlersMap.has(rpcName), `Handler for rpc '${rpcName}' already registered`);

    const rpcHandler = new RPCHandler(rpcName, handler);
    rpcHandlersMap.set(rpcName, rpcHandler);
    return rpcHandler;
};

alt.Events.onScriptRPC(async (ctx) => {
    const answerID = ctx.answerID;

    ctx.willAnswer();

    if (!rpcHandlersMap.has(ctx.name)) {
        cppBindings.answerRPC(ctx.player, answerID, undefined, `No handler for RPC '${ctx.name}' registered`);
        return;
    }

    const { handler } = rpcHandlersMap.get(ctx.name);

    try {
        const args = [ctx.player, ...ctx.args];

        let result = handler(args);

        if (result instanceof Promise) {
            result = await result;
        }

        cppBindings.answerRPC(ctx.player, answerID, result);
    } catch (e) {
        cppBindings.answerRPC(ctx.player, answerID, undefined, e.message);
    }
});
