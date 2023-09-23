/** @type {typeof import("../helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.WatermarkPosition = createNumericEnum(["BOTTOM_RIGHT", "TOP_RIGHT", "TOP_LEFT", "TOP_CENTER", "BOTTOM_CENTER"]);
