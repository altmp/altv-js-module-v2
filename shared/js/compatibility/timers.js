/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/timers.js");

/**
 *
 * @param {Function} callback
 * @returns
 */
function everyTick(callback) {
    const timer = alt.Timers.everyTick(callback);
    return timer.id;
}

/**
 *
 * @param {Function} callback
 */
function nextTick(callback) {
    const timer = alt.Timers.nextTick(callback);
    return timer.id;
}

/**
 *
 * @param {Function} callback
 * @param {number} interval
 * @returns
 */
function setInterval(callback, interval) {
    const timer = alt.Timers.setInterval(callback, interval);
    return timer.id;
}

/**
 *
 * @param {Function} callback
 * @param {number} timeout
 * @returns
 */
function setTimeout(callback, timeout) {
    const timer = alt.Timers.setTimeout(callback, timeout);
    return timer.id;
}

/**
 *
 * @param {number} id
 */
function removeTimer(id) {
    const timer = alt.Timers.getByID(id);
    timer?.destroy();
}

cppBindings.registerCompatibilityExport("everyTick", everyTick);
cppBindings.registerCompatibilityExport("nextTick", nextTick);
cppBindings.registerCompatibilityExport("setInterval", setInterval);
cppBindings.registerCompatibilityExport("setTimeout", setTimeout);
cppBindings.registerCompatibilityExport("time", alt.Timers.time);
cppBindings.registerCompatibilityExport("timeEnd", alt.Timers.timeEnd);

cppBindings.registerCompatibilityExport("clearEveryTick", removeTimer);
cppBindings.registerCompatibilityExport("clearInterval", removeTimer);
cppBindings.registerCompatibilityExport("clearNextTick", removeTimer);
cppBindings.registerCompatibilityExport("clearTimeout", removeTimer);
cppBindings.registerCompatibilityExport("clearTimer", removeTimer);
