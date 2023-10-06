/** @type {typeof import("../helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

alt.Enums.VehiclePart = createNumericEnum(["FRONT_LEFT", "FRONT_RIGHT", "MIDDLE_LEFT", "MIDDLE_RIGHT", "REAR_LEFT", "REAR_RIGHT"]);
