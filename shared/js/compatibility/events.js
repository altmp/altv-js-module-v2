/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function on(eventName, callback) {
    async function wrapper(ctx) {
        const callbackRet = callback(ctx);

        let processedResult = callbackRet;
        if (callbackRet instanceof Promise) {
            processedResult = await callbackRet;
        }

        if (processedResult === false && ctx.isCancellable) {
            ctx.cancel();
        }
    }

    alt.Events.on(eventName, wrapper);
}

/**
 *
 * @param {string} eventName
 * @param {Function} callback
 */
function once(eventName, callback) {
    if (typeof callback != "function") throw new Error("callback is not a function");

    async function wrapper(...args) {
        const ret = callback(...args);
        alt.Events.on.remove(eventName, wrapper);

        if (ret instanceof Promise) await ret;
    }

    alt.Events.on(eventName, wrapper);
}

/**
 *
 * @param {string | undefined} eventName
 */
function getEventListeners(eventName) {
    const listeners = typeof eventName == "string" ? alt.Events.on.listeners[eventName] : alt.Events.on.listeners;
    return listeners ?? [];
}

cppBindings.registerCompatibilityExport("on", on);
cppBindings.registerCompatibilityExport("once", once);
cppBindings.registerCompatibilityExport("off", alt.Events.onEvent.remove);
cppBindings.registerCompatibilityExport("getEventListeners", getEventListeners);
