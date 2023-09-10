/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/**
 *
 * @param {string} eventName
 * @param {unknown[]} args
 */
function emitRaw(eventName, ...args) {
    const oldValue = alt.Events.rawEmitEnabled;

    alt.Events.rawEmitEnabled = true;
    this.emit(eventName, ...args);
    alt.Events.rawEmitEnabled = oldValue;
}

alt.Player.prototype.emitRaw = emitRaw;
