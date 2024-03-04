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
            if (Date.now() > checkUntil) {
                this.destroy();
                return reject(new Error("Timeout"));
            }
            if (cb()) {
                this.destroy();
                return resolve();
            }
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

export function isObject(value) {
    return value !== null && typeof value === "object";
}

export function assertIsObject(value, message) {
    assert(isObject(value), message);
}

export function assertIsType(value, type, message) {
    assert(typeof value === type, message);
}

export function assertIsOneOfType(value, types, message) {
    assert(
        types.some((type) => typeof value === type),
        message
    );
}

export function assertNotNaN(val, message = "Expected number") {
    assert(!isNaN(val), message);
}

export function assertRGBA(val, message = "Expected RGBA") {
    return assert(val && typeof val.r === "number" && typeof val.g === "number" && typeof val.b === "number" && typeof val.a === "number", message);
}

export function isVector2(val) {
    return val && typeof val.x === "number" && typeof val.y === "number";
}

export function assertVector2(val, message = "Expected Vector2") {
    return assert(isVector2(val), message);
}

export function isVector3(val) {
    return val && typeof val.x === "number" && typeof val.y === "number" && typeof val.z === "number";
}

export function assertVector3(val, message = "Expected Vector3") {
    return assert(isVector3(val), message);
}

alt.Utils.AssertionError = AssertionError;
alt.Utils.assert = assert;
alt.Utils.assertIsObject = assertIsObject;
alt.Utils.assertIsType = assertIsType;
alt.Utils.assertNotNaN = assertNotNaN;
alt.Utils.assertRGBA = assertRGBA;
alt.Utils.assertVector2 = assertVector2;
alt.Utils.assertVector3 = assertVector3;

alt.Utils.isVector2 = isVector2;
alt.Utils.isVector3 = isVector3;

export function hash(str) {
    assertIsType(str, "string", "Expected a string as first argument");

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

cppBindings.registerExport(cppBindings.BindingExport.HASH, hash);
