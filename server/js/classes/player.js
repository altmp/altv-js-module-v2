/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />

/** @type {typeof import("../../../shared/js/helpers/scriptEvents.js")} */
const { emitRaw } = requireBinding("shared/helpers/scriptEvents.js");

alt.Player.prototype.emitRaw = emitRaw();
alt.Player.prototype.emitUnreliableRaw = emitRaw("emitUnreliable");
