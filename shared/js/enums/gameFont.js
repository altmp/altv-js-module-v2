/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.GameFont = createReverseLookupObject({
    CHALET_LONDON: 0,
    HOUSE_SCRIPT: 1,
    MONOSPACE: 2,
    CHARLET_COMPRIME_COLONGE: 4,
    PRICEDOWN: 7
});
