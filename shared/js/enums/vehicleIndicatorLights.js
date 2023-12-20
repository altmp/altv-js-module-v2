/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.VehicleIndicatorLights = createReverseLookupObject({
    NONE: 0,
    BLINK_LEFT: 1,
    BLINK_RIGHT: 2,
    BLINK_PERM_BOTH: 4,
    STATIC_BOTH: 8,
    INTERIOR: 64
});
