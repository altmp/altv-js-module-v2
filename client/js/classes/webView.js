/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />

/** @type {typeof import("../../../shared/js/helpers/events.js")} */
const { emitRaw } = requireBinding("shared/helpers/events.js");

alt.WebView.prototype.emitRaw = emitRaw();
