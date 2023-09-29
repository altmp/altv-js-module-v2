requireBinding("shared/events.js");
/** @type {typeof import("./utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");
requireBinding("shared/events/console.js");

class Command {
    /** @type {Map<string, Function[]} */
    static #commands = new Map();

    static register(command, callback) {
        assertIsType(command, "string", "Command name must be a string");
        assertIsType(callback, "function", "Command callback must be a function");

        if (Command.#commands.has(command)) Command.#commands.get(command).push(callback);
        else Command.#commands.set(command, [callback]);
    }

    static unregister(command, callback) {
        assertIsType(command, "string", "Command name must be a string");
        assertIsType(callback, "function", "Command callback must be a function");

        const callbacks = Command.#commands.get(command);
        if (!callbacks) return;
        const index = callbacks.indexOf(callback);
        if (index === -1) return;
        callbacks.splice(index, 1);
    }

    static onCommand(command, args) {
        const callbacks = Command.#commands.get(command);
        if (!callbacks) return;
        for (const callback of callbacks) callback(...args);
    }
}

alt.Commands.register = Command.register;
alt.Commands.unregister = Command.unregister;

alt.Events.onConsoleCommand(({ command, args }) => {
    Command.onCommand(command, args);
});
