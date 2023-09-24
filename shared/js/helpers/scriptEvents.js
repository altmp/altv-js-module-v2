export function emitRaw(fn = "emit") {
    return function (eventName, ...args) {
        const oldValue = alt.Events.rawEmitEnabled;

        alt.Events.rawEmitEnabled = true;
        this[fn](eventName, ...args);
        alt.Events.rawEmitEnabled = oldValue;
    };
}
