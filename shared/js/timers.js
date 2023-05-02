/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

/** @type {Set<Timer>} */
const timers = new Set();

class Timer {
    static #warningThreshold = 100;
    static setWarningThreshold(threshold) {
        assert(typeof threshold === "number", "Expected a number as first argument");
        Timer.#warningThreshold = threshold;
    }

    static #sourceLocationFrameSkipCount = 0;
    static setSourceLocationFrameSkipCount(count) {
        assert(typeof count === "number", "Expected a number as first argument");
        Timer.#sourceLocationFrameSkipCount = count;
    }

    /** @type {number} */
    interval;
    /** @type {Function} */
    callback;
    /** @type {number} */
    lastTick;
    /** @type {boolean} */
    once;
    /** @type {{ fileName: string, lineNumber: number }} */
    location;

    constructor(callback, interval, once) {
        assert(typeof callback === "function", "Expected a function as first argument");
        assert(typeof interval === "number", "Expected a number as second argument");

        this.interval = interval;
        this.callback = callback.bind(this);
        this.lastTick = Date.now();
        this.once = once;
        this.location = cppBindings.getCurrentSourceLocation(Timer.#sourceLocationFrameSkipCount);
        timers.add(this);
    }

    destroy() {
        timers.delete(this);
    }

    tick() {
        if (this.interval === 0 || Date.now() - this.lastTick > this.interval) {
            const start = Date.now();
            try {
                this.callback();
            } catch (e) {
                alt.logError(`[JS] Exception caught while invoking timer callback`);
                alt.logError(e);
            }
            this.lastTick = Date.now();
            if (this.once) this.destroy();

            const duration = this.lastTick - start;
            if (duration > Timer.#warningThreshold) {
                alt.logWarning(
                    `[JS] Timer callback in resource '${cppBindings.resourceName}' (${this.location.fileName}:${
                        this.location.lineNumber
                    }) took ${duration}ms to execute (Threshold: ${Timer.#warningThreshold}ms)`
                );
            }
        }
    }
}

class Interval extends Timer {
    constructor(callback, interval) {
        super(callback, interval, false);
    }
}

class Timeout extends Timer {
    constructor(callback, interval) {
        super(callback, interval, true);
    }
}

class EveryTick extends Timer {
    constructor(callback) {
        super(callback, 0, false);
    }
}

class NextTick extends Timer {
    constructor(callback) {
        super(callback, 0, true);
    }
}

alt.Timers.Interval = Interval;
alt.Timers.Timeout = Timeout;
alt.Timers.EveryTick = EveryTick;
alt.Timers.NextTick = NextTick;
alt.Timers.setWarningThreshold = Timer.setWarningThreshold;
alt.Timers.setSourceLocationFrameSkipCount = Timer.setSourceLocationFrameSkipCount;

alt.Timers.setInterval = (callback, interval) => new Interval(callback, interval);
alt.Timers.setTimeout = (callback, interval) => new Timeout(callback, interval);
alt.Timers.everyTick = (callback) => new EveryTick(callback);
alt.Timers.nextTick = (callback) => new NextTick(callback);

Object.defineProperty(alt.Timers, "all", {
    get: () => Array.from(timers),
});

globalThis.setInterval = alt.Timers.setInterval;
globalThis.setTimeout = alt.Timers.setTimeout;

globalThis.clearInterval = (interval) => {
    if (!(interval instanceof Interval)) throw new Error("Expected an Interval as first argument");
    interval.destroy();
};
globalThis.clearTimeout = (timeout) => {
    if (!(timeout instanceof Timeout)) throw new Error("Expected a Timeout as first argument");
    timeout.destroy();
};

function tick() {
    for (const timer of timers) {
        timer.tick();
    }
}
cppBindings.registerExport("timers:tick", tick);
