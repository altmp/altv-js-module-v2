// clang-format off
const timers = new Set();

class Timer {
    constructor(interval, callback, once) {
        this.interval = interval;
        this.callback = callback;
        this.lastTick = 0;
        this.once = once;
        timers.add(this);
    }

    destroy() {
        timers.delete(this);
    }

    tick() {
        if (this.interval === 0 || (Date.now() - this.lastTick > this.interval)) {
            this.callback();
            this.lastTick = Date.now();
            if (this.once) this.destroy();
        }
    }
}

class Interval extends Timer {
    constructor(interval, callback) { super(interval, callback, false); }
}

class Timeout extends Timer {
    constructor(interval, callback) { super(interval, callback, true); }
}

class EveryTick extends Timer {
    constructor(callback) { super(0, callback, false); }
}

class NextTick extends Timer {
    constructor(callback) { super(0, callback, true); }
}

alt.Timers.Interval = Interval;
alt.Timers.Timeout = Timeout;
alt.Timers.EveryTick = EveryTick;
alt.Timers.NextTick = NextTick;

export function tick() {
    for (const timer of timers) timer.tick();
}
