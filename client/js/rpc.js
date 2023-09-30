/** @type {typeof import("./utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

/**
 * @type {Map<number, { resolve: Function, reject: Function }>}
 */
const pendingRpcMap = new Map();

alt.RPC.send = function (rpcName, ...args) {
    assertIsType(rpcName, "string", "rpcName has to be a string");

    const answerID = cppBindings.sendRPC(rpcName, ...args);
    const result = new Promise((resolve, reject) => {
        pendingRpcMap.set(answerID, { resolve, reject });
    });
    return result;
};

alt.Events.ScriptRPCAnswer(async ({ answerID, answer, answerError }) => {
    if (!pendingRpcMap.has(answerID)) return;
    const { resolve, reject } = pendingRpcMap.get(answerID);
    if (answerError.length !== 0) reject(answerError);
    else resolve(answer);
    pendingRpcMap.delete(answerID);
});
