/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.TextAlign = createNumericEnum(["CENTER", "LEFT", "RIGHT"]);
