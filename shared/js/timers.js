/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

/** @type {Set<Timer>} */
const timers = new Set();

class Timer {
    static #_warningThreshold = 100;
    static set warningThreshold(threshold) {
        assert(typeof threshold === "number", "Expected a number as first argument");
        Timer.#_warningThreshold = threshold;
    }

    static get warningThreshold() {
        return Timer.#_warningThreshold;
    }

    static #_sourceLocationFrameSkipCount = 0;
    static set sourceLocationFrameSkipCount(count) {
        assert(typeof count === "number", "Expected a number as first argument");
        Timer.#_sourceLocationFrameSkipCount = count;
    }

    static get sourceLocationFrameSkipCount() {
        return Timer.#_sourceLocationFrameSkipCount;
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

    /** @type {string} */
    #_type = "Timer";

    get type() {
        return this.#_type;
    }

    constructor(type, callback, interval, once) {
        assert(typeof type === "string", "Expected a string as first argument");
        assert(typeof callback === "function", "Expected a function as second argument");
        assert(typeof interval === "number", "Expected a number as third argument");

        this.interval = interval;
        this.callback = callback.bind(this);
        this.lastTick = Date.now();
        this.once = once;
        this.#_type = type;
        this.location = cppBindings.getCurrentSourceLocation(Timer.#_sourceLocationFrameSkipCount);
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
            if (duration > Timer.#_warningThreshold) {
                alt.logWarning(
                    `[JS] Timer callback in resource '${cppBindings.resourceName}' (${this.location.fileName}:${this.location.lineNumber
                    }) took ${duration}ms to execute (Threshold: ${Timer.#_warningThreshold}ms)`
                );
            }
        }
    }
}

class Interval extends Timer {
    constructor(callback, interval) {
        super("Interval", callback, interval, false);
    }
}

class Timeout extends Timer {
    constructor(callback, interval) {
        super("Timeout", callback, interval, true);
    }
}

class EveryTick extends Timer {
    constructor(callback) {
        super("EveryTick", callback, 0, false);
    }
}

class NextTick extends Timer {
    constructor(callback) {
        super("NextTick", callback, 0, true);
    }
}

alt.Timers.Interval = Interval;
alt.Timers.Timeout = Timeout;
alt.Timers.EveryTick = EveryTick;
alt.Timers.NextTick = NextTick;

alt.Timers.warningThreshold = Timer.warningThreshold
alt.Timers.sourceLocationFrameSkipCount = Timer.sourceLocationFrameSkipCount

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
