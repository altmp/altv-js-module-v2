/** @type {typeof import("./utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");
/** @type {typeof import("../../shared/js/rpc.js")} */
const { answerRpc, sendRpc } = requireBinding("shared/rpc.js");

/**
 * @type {Map<alt.Player, Map<number, { resolve: Function, reject: Function }>>}
 */
const pendingRpcMap = new Map();

alt.Player.prototype.sendRPC = function (rpcName, ...args) {
    assertIsType(rpcName, "string", "rpcName has to be a string");

    const result = sendRpc(rpcName, this, ...args);
    let map = pendingRpcMap.get(this);
    if (!map) {
        map = new Map();
        pendingRpcMap.set(this, map);
    }
    map.set(result.answerID, { resolve: result.resolve, reject: result.reject });
    return result.promise;
};

alt.Events.onScriptRPCAnswer((ctx) => {
    const map = pendingRpcMap.get(ctx.player);
    if (!map) return;
    answerRpc(ctx, map);
});
