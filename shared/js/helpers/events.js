/**
 * Creates a function that calls the emit function
 * with the rawEmitEnabled flag set to true.
 *
 * @param {string} fn
 * @returns {(eventName: string, ...args: unknown[]) => void}
 */
export function emitRaw(fn = "emit") {
    return function (eventName, ...args) {
        const oldValue = alt.Events.rawEmitEnabled;

        alt.Events.rawEmitEnabled = true;
        this[fn](eventName, ...args);
        alt.Events.rawEmitEnabled = oldValue;
    };
}
