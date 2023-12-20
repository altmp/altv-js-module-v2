/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.VehicleDoorState = createReverseLookupObject({
    CLOSED: 0,
    OPENED_LEVEL_1: 1,
    OPENED_LEVEL_2: 2,
    OPENED_LEVEL_3: 3,
    OPENED_LEVEL_4: 4,
    OPENED_LEVEL_5: 5,
    OPENED_LEVEL_6: 6,
    OPENED_LEVEL_7: 7,
    UNKNOWN: 255
});
