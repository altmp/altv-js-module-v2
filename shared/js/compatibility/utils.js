/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("./../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

requireBinding("shared/events/console.js");

class Timer {
    constructor(callback, ms, once) {
        assertIsType(callback, "function");
        assertIsType(ms, "number");

        if (once) return new alt.Timers.setTimeout(callback, ms);
        return new alt.Timers.setInterval(callback, ms);
    }
}

class ConsoleCommand {
    static registeredCommands = new Map();

    #commandName;
    #callback;

    constructor(name, callback) {
        assertIsType(name, "string");
        assertIsType(callback, "function");

        name = name.toLowerCase();

        this.#commandName = name;
        this.#callback = callback;

        const handlers = ConsoleCommand.registeredCommands.get(name) ?? [];
        handlers.push(callback);
        ConsoleCommand.registeredCommands.set(name, handlers);
    }

    get callback() {
        return this.#callback;
    }

    destroy() {
        const registeredCommands = (ConsoleCommand.registeredCommands.get(this.#commandName) ?? []).filter((command) => command != this);

        if (registeredCommands.length) ConsoleCommand.registeredCommands.set(this.#commandName, registeredCommands);
        else Keybind.registeredHandlers.delete(this.keyCode);
    }
}

alt.Events.onConsoleCommand(({ command, args }) => {
    command = command.toLowerCase();

    if (!ConsoleCommand.registeredCommands.has(command)) return;

    const handlers = ConsoleCommand.registeredCommands.get(command);

    for (const handler of handlers) {
        handler?.(...args);
    }
});

export class SharedUtils {
    static wait = alt.Utils.wait;
    static waitFor = alt.Utils.waitFor;

    static inspect = alt.Utils.inspect;
    static assert = alt.Utils.assert;

    static ConsoleCommand = ConsoleCommand;

    static Timer = Timer;
    static Timeout = alt.Timers.Timeout;
    static Interval = alt.Timers.Interval;
    static NextTick = alt.Timers.NextTick;
    static EveryTick = alt.Timers.EveryTick;
}

if (alt.isServer) {
    // NOTE (xLuxy): Server has no Utilities
    cppBindings.registerCompatibilityExport("Utils", SharedUtils);
}
