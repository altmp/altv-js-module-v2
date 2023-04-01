requireBinding("shared/timers.js");
const { inspect } = requireBinding("shared/logging.js");

alt.Utils.inspect = inspect;

alt.Utils.wait = (ms) => new Promise((resolve) => alt.Timers.setTimeout(resolve, ms));
alt.Utils.waitForNextTick = () => alt.Utils.wait(0);
alt.Utils.waitFor = (cb, timeout) => {
    const checkUntil = Date.now() + timeout;
    return new Promise((resolve, reject) => {
        alt.Timers.everyTick(function () {
            if (Date.now() > checkUntil) return reject(new Error("Timeout"));
            if (cb()) return resolve();
            this.destroy();
        });
    });
};

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
