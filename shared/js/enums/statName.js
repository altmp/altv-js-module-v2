/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.StatName = createReverseLookupObject({
    STAMINA: "stamina",
    STRENGTH: "strength",
    LUNG_CAPACITY: "lung_capacity",
    WHEELIE: "wheelie_ability",
    FLYING: "flying_ability",
    SHOOTING: "shooting_ability",
    STEALTH: "stealth_ability"
});
