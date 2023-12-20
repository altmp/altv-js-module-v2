/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

alt.Enums.BaseObjectFilterType = createReverseLookupObject({
    PLAYER: 1,
    VEHICLE: 2,
    PED: 4,
    OBJECT: 8
});
