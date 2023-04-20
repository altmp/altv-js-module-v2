/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");
const timers = new Set();

class Timer {
    interval;
    callback;
    lastTick;
    once;

    constructor(interval, callback, once) {
        assert(typeof interval === "number", "Expected a number as first argument");
        assert(typeof callback === "function", "Expected a function as second argument");

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
            this.callback();
            this.lastTick = Date.now();
            if (this.once) this.destroy();
        }
    }
}

class Interval extends Timer {
    constructor(callback, interval) {
        super(interval, callback, false);
    }
}

class Timeout extends Timer {
    constructor(callback, interval) {
        super(interval, callback, true);
    }
}

class EveryTick extends Timer {
    constructor(callback) {
        super(0, callback, false);
    }
}

class NextTick extends Timer {
    constructor(callback) {
        super(0, callback, true);
    }
}

alt.Timers.Interval = Interval;
alt.Timers.Timeout = Timeout;
alt.Timers.EveryTick = EveryTick;
alt.Timers.NextTick = NextTick;

alt.Timers.setInterval = (interval, callback) => new Interval(interval, callback);
alt.Timers.setTimeout = (interval, callback) => new Timeout(interval, callback);
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
        }
    }
}
