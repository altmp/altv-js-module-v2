/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.TimerType = createNumericEnum(["TIMER", "INTERVAL", "TIMEOUT", "EVERY_TICK", "NEXT_TICK"]);
