/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

alt.Enums.FileEncoding = createReverseLookupObject({
    Utf8: "utf-8",
    Utf16: "utf-16",
    Binary: "binary"
});
