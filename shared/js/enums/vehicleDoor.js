/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

alt.Enums.VehicleDoor = createNumericEnum(["DRIVER_FRONT", "PASSENGER_FRONT", "DRIVER_REAR", "PASSENGER_REAR", "HOOD", "TRUNK"]);
