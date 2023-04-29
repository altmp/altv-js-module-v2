const { inspect } = requireBinding("shared/logging.js");

alt.Utils.inspect = inspect;

export function wait(ms) {
    return new Promise((resolve) => alt.Timers.setTimeout(resolve, ms));
}
export function waitForNextTick() {
    return wait(0);
}
export function waitFor(cb, timeout) {
    const checkUntil = Date.now() + timeout;
    return new Promise((resolve, reject) => {
        alt.Timers.everyTick(function () {
            if (Date.now() > checkUntil) return reject(new Error("Timeout"));
            if (cb()) return resolve();
            this.destroy();
        });
    });
}

alt.Utils.wait = wait;
alt.Utils.waitForNextTick = waitForNextTick;
alt.Utils.waitFor = waitFor;
alt.Utils.getCurrentSourceLocation = cppBindings.getCurrentSourceLocation;

export class AssertionError extends Error {}
export function assert(condition, message) {
    if (!condition) throw new alt.Utils.AssertionError(message ?? "Assertion failed");
}
export function assertIsObject(value, message) {
    assert(value !== null && typeof value === "object", message);
}
alt.Utils.AssertionError = AssertionError;
alt.Utils.assert = assert;

export function hash(str) {
    if (typeof str !== "string") throw new Error("Expected a string as first argument");

    const string = str.toLowerCase();
    const length = string.length;
    let hash = 0;
    for (let i = 0; i < length; i++) {
        hash += string.charCodeAt(i);
        hash += hash << 10;
        hash ^= hash >>> 6;
    }

    hash += hash << 3;
    hash ^= hash >>> 11;
    hash += hash << 15;

    return hash >>> 0; // Convert to unsigned
}
