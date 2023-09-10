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
    alt.Events.on(eventName, callback);
}

function once(eventName, callback) {
    if (typeof callback != "function") throw new Error("callback is not a function");

    // TODO (xLuxy): Fix this - handler wont be removed
    alt.logWarning("alt.once does currently not work as expected.");

    async function wrapper({ args }) {
        const ret = callback(...args);
        alt.Events.onEvent.remove(wrapper);

        if (ret instanceof Promise) await ret;
    }

    alt.Events.on(eventName, wrapper);
}

// TODO (xLuxy): Implement this
function getEventListeners(eventName) {
    throw new Error("getEventListeners is not implemented");
}

cppBindings.registerCompatibilityExport("on", on);
cppBindings.registerCompatibilityExport("once", once);
cppBindings.registerCompatibilityExport("off", alt.Events.onEvent.remove);
cppBindings.registerCompatibilityExport("getEventListeners", getEventListeners);
