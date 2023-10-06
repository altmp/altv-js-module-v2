/** @type {typeof import("../helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

alt.Enums.VehiclePartDamage = createNumericEnum(["NOT_DAMAGED", "DAMAGED_LEVEL_1", "DAMAGED_LEVEL_2", "DAMAGED_LEVEL_3"]);
