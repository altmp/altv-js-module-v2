/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.Weather = createNumericEnum([
    'ExtraSunny',
    'Clear',
    'Clouds',
    'Smog',
    'Foggy',
    'Overcast',
    'Rain',
    'Thunder',
    'LightRain',
    'SmoggyLightRain',
    'VeryLightSnow',
    'WindyLightSnow',
    'LightSnow',
    'Christmas',
    'Halloween',
]);
