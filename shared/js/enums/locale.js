/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.Locale = createReverseLookupObject({
    ARABIC: "ar",
    BELARUSIAN: "by",
    CZECH: "cz",
    GERMAN: "de",
    ENGLISH: "en",
    SPANISH: "es",
    FARSI: "fa",
    FRENCH: "fr",
    HEBREW: "he",
    HUNGARIAN: "hu",
    INDONESIAN: "id",
    HINDI: "in_hd",
    MALAYALAM: "in_ml",
    TELUGU: "in_tl",
    TAMIL: "in_tm",
    ITALIAN: "it",
    LITHUANIAN: "lt",
    LATVIAN: "lv",
    NORWEGIAN_BOKMAL: "nb_no",
    NORWEGIAN_NYNORSK: "nn_no",
    POLISH: "pl",
    PORTUGESE: "pt",
    BRAZILIAN_PORTUGUESE: "pt_br",
    ROMANIAN: "ro",
    SERBIAN: "rs",
    RUSSIAN: "ru",
    SLOVAK: "sk",
    THAI: "th",
    TURKISH: "tr",
    UKRAINIAN: "ua",
    CHINESE_SIMPLIFIED: "zh_cn",
    CHINESE_TRADITIONAL: "zh_tw"
});
