/** @type {typeof import("./utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");
/** @type {typeof import("../../shared/js/rpc.js")} */
const { answerRpc, sendRpc } = requireBinding("shared/rpc.js");

/**
 * @type {Map<number, { resolve: Function, reject: Function }>}
 */
const pendingRpcMap = new Map();

alt.RPC.send = function (rpcName, ...args) {
    assertIsType(rpcName, "string", "rpcName has to be a string");

    const result = sendRpc(rpcName, ...args);
    pendingRpcMap.set(result.answerID, { resolve: result.resolve, reject: result.reject });
    return result.promise;
};

alt.Events.onScriptRPCAnswer((ctx) => {
    answerRpc(ctx, pendingRpcMap);
});
