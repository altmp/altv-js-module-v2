/** @type {typeof import("../helpers/enums.js")} */
const { createReverseLookupObject } = requireBinding("shared/helpers/enums.js");

alt.Enums.FileEncoding = createReverseLookupObject({
    UTF8: "utf-8",
    UTF16: "utf-16",
    BINARY: "binary"
});
