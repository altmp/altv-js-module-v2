/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />

/** @type {typeof import("../../../shared/js/helpers/events.js")} */
const { emitRaw } = requireBinding("shared/helpers/events.js");

alt.Player.prototype.emitRaw = emitRaw();
alt.Player.prototype.emitUnreliableRaw = emitRaw("emitUnreliable");
