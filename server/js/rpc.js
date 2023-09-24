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

alt.Events.onPlayerScriptRPC(async (ctx) => {
    if (!rpcHandlersMap.has(ctx.name)) return;
    const handler = rpcHandlersMap.get(ctx.name);

    let result;
    try {
        const args = [ctx.player, ...ctx.args];
        result = handler(args);
    } catch (e) {
        ctx.answerWithError(e.message);
        return;
    }

    if (result instanceof Promise) {
        const answerID = ctx.answerID;
        ctx.willAnswer();
        let asyncAnswer;
        try {
            asyncAnswer = await result;
        } catch (e) {
            cppBindings.answerRPC(ctx.player, answerID, undefined, e.message);
            return;
        }
        cppBindings.answerRPC(ctx.player, answerID, asyncAnswer);
    } else ctx.answer(result);
});
