/** @type {typeof import("../helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

alt.Enums.VehicleWindowTint = createNumericEnum(["NONE", "PURE_BLACK", "DARK_SMOKE", "LIGHT_SMOKE", "STOCK", "LIMO", "GREEN"]);
