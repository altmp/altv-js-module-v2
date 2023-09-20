/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

/** @type {Map<number, Timer>} */
const timers = new Map();

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

    /** @type {number} */
    #_id = 0;

    get type() {
        return this.#_type;
    }

    get id() {
        return this.#_id;
    }

    /**
     * @type {number}
     */
    static #timerIncrementer = 1;

    /**
     * @param {number} id
     */
    static getByID(id) {
        return timers.get(id) || null;
    }

    constructor(type, callback, interval, once, args) {
        assert(typeof type === "string", "Expected a string as first argument");
        assert(typeof callback === "function", "Expected a function as second argument");
        assert(typeof interval === "number", "Expected a number as third argument");

        this.interval = interval;
        this.callback = callback.bind(this, ...(Array.isArray(args) ? args : []));
        this.lastTick = Date.now();
        this.once = once;
        this.#_type = type;
        this.#_id = Timer.#timerIncrementer++;
        this.location = cppBindings.getCurrentSourceLocation(Timer.#_sourceLocationFrameSkipCount);
        timers.set(this.#_id, this);
    }

    destroy() {
        timers.delete(this.#_id);
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
                alt.logWarning(`[JS] Timer callback in resource '${cppBindings.resourceName}' (${this.location.fileName}:${this.location.lineNumber}) took ${duration}ms to execute (Threshold: ${Timer.#_warningThreshold}ms)`);
            }
        }
    }
}

class Interval extends Timer {
    constructor(callback, interval, ...args) {
        super("Interval", callback, interval, false, args);
    }
}

class Timeout extends Timer {
    constructor(callback, interval, ...args) {
        super("Timeout", callback, interval, true, args);
    }
}

class EveryTick extends Timer {
    constructor(callback, ...args) {
        super("EveryTick", callback, 0, false, args);
    }
}

class NextTick extends Timer {
    constructor(callback, ...args) {
        super("NextTick", callback, 0, true, args);
    }
}

const timeMap = new Map();

/**
 *
 * @param {string | undefined} name
 */
function time(name) {
    const key = typeof name == "string" ? name : "";

    if (timeMap.has(key)) {
        throw new Error(`Benchmark timer ${timer} already exists`);
    }

    timeMap.set(key, Date.now());
}

/**
 *
 * @param {string | undefined} name
 */
function timeEnd(name) {
    const key = typeof name == "string" ? name : "";

    if (!timeMap.has(key)) {
        throw new Error(`Benchmark timer ${timer} not found`);
    }

    const diff = Date.now() - timeMap.get(key);
    timeMap.delete(key);

    alt.log(`Timer ${key}: ${diff}ms`);
}

alt.Timers.Interval = Interval;
alt.Timers.Timeout = Timeout;
alt.Timers.EveryTick = EveryTick;
alt.Timers.NextTick = NextTick;

alt.Timers.getByID = Timer.getByID;

alt.Timers.setInterval = (callback, interval, ...args) => new Interval(callback, interval, ...args);
alt.Timers.setTimeout = (callback, interval, ...args) => new Timeout(callback, interval, ...args);
alt.Timers.everyTick = (callback, ...args) => new EveryTick(callback, ...args);
alt.Timers.nextTick = (callback, ...args) => new NextTick(callback, ...args);

alt.Timers.time = time;
alt.Timers.timeEnd = timeEnd;

Object.defineProperty(alt.Timers, "all", {
    get: () => Array.from(timers.values())
});

Object.defineProperty(alt.Timers, "warningThreshold", {
    get: () => Timer.warningThreshold,
    set: (value) => (Timer.warningThreshold = value)
});

Object.defineProperty(alt.Timers, "sourceLocationFrameSkipCount", {
    get: () => Timer.sourceLocationFrameSkipCount,
    set: (value) => (Timer.sourceLocationFrameSkipCount = value)
});

globalThis.setInterval = alt.Timers.setInterval;
globalThis.setTimeout = alt.Timers.setTimeout;

globalThis.time = alt.Timers.time;
globalThis.timeEnd = alt.Timers.timeEnd;

globalThis.clearInterval = (interval) => {
    if (interval === null || interval === undefined) return;
    if (!(interval instanceof Interval)) throw new Error("Expected an Interval as first argument");
    interval.destroy();
};
globalThis.clearTimeout = (timeout) => {
    if (timeout === null || timeout === undefined) return;
    if (!(timeout instanceof Timeout)) throw new Error("Expected a Timeout as first argument");
    timeout.destroy();
};

function tick() {
    for (const [_, timer] of timers) {
        timer.tick();
    }
}
cppBindings.registerExport("timers:tick", tick);
