/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />

/** @type {typeof import("../../../shared/js/helpers/scriptEvents.js")} */
const { emitRaw } = requireBinding("shared/helpers/scriptEvents.js");

alt.WebView.prototype.emitRaw = emitRaw();
