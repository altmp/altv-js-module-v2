/** @type {typeof import("../helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.WebSocketReadyState = createNumericEnum(["CONNECTING", "OPEN", "CLOSING", "CLOSED"]);
