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

    interval;
    callback;
    lastTick;
    once;

    constructor(callback, interval, once) {
        assert(typeof callback === "function", "Expected a function as first argument");
        assert(typeof interval === "number", "Expected a number as second argument");

        this.interval = interval;
        this.callback = callback.bind(this);
        this.lastTick = Date.now();
        this.once = once;
        timers.add(this);
    }

    destroy() {
        timers.delete(this);
    }

    tick() {
        if (this.interval === 0 || Date.now() - this.lastTick > this.interval) {
            const start = Date.now();
            this.callback();
            this.lastTick = Date.now();
            if (this.once) this.destroy();

            const duration = this.lastTick - start;
            if (duration > Timer.#warningThreshold) {
                alt.logWarning(
                    `[JS] Timer callback took ${duration}ms to execute (Threshold: ${Timer.#warningThreshold}ms)`
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

alt.Timers.setInterval = (callback, interval) => new Interval(callback, interval);
alt.Timers.setTimeout = (callback, interval) => new Timeout(callback, interval);
alt.Timers.everyTick = (callback) => new EveryTick(callback);
alt.Timers.nextTick = (callback) => new NextTick(callback);

alt.Timers.getTimers = () => {
    return Array.from(timers);
};

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

export function tick() {
    for (const timer of timers) {
        try {
            timer.tick();
        } catch (e) {
            alt.logError(`[JS] Exception caught while invoking timer callback`);
            alt.logError(e);
            if (timer.once) timer.destroy();
        }
    }
}
