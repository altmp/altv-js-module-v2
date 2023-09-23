/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.Weather = createNumericEnum(["EXTRA_SUNNY", "CLEAR", "CLOUDS", "SMOG", "FOGGY", "OVERCAST", "RAIN", "THUNDER", "LIGHT_RAIN", "SMOGGY_LIGHT_RAIN", "VERY_LIGHT_SNOW", "WINDY_LIGHT_SNOW", "LIGHT_SNOW", "CHRISTMAS", "HALLOWEEN"]);
