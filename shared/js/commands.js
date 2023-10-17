requireBinding("shared/events.js");
/** @type {typeof import("./utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");
requireBinding("shared/events/console.js");

class Command {
    /** @type {Map<string, Function} */
    static #commands = new Map();

    static register(command, callback) {
        assertIsType(command, "string", "Command name must be a string");
        assertIsType(callback, "function", "Command callback must be a function");
        assert(!Command.#commands.has(command), `Command '${command}' is already registered`);

        Command.#commands.set(command, callback);
    }

    static unregister(command, callback) {
        assertIsType(command, "string", "Command name must be a string");
        assertIsType(callback, "function", "Command callback must be a function");

        Command.#commands.delete(command);
    }

    static onCommand(command, args) {
        const callback = Command.#commands.get(command);
        if (!callback) return;
        callback(...args);
    }
}

alt.Commands.register = Command.register;
alt.Commands.unregister = Command.unregister;

alt.Events.onConsoleCommand(({ command, args }) => {
    Command.onCommand(command, args);
});
