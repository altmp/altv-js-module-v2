/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.RESOURCE_START, "anyResourceStart", ({ resource }) => {
    return [resource.name];
});

registerEventHandler(alt.Enums.EventType.RESOURCE_STOP, "anyResourceStop", ({ resource }) => {
    return [resource.name];
});

registerEventHandler(alt.Enums.EventType.RESOURCE_ERROR, "anyResourceError", ({ resource }) => {
    return [resource.name];
});

registerEventHandler(
    alt.Enums.CustomEventType.ERROR,
    "resourceError",
    ({ error, location, stack }) => {
        const { fileName, lineNumber } = location;

        return [error, fileName, lineNumber, stack];
    },
    true
);

registerEventHandler(
    alt.Enums.CustomEventType.RESOURCE_START,
    "resourceStart",
    () => {
        return [];
    },
    true
);

registerEventHandler(
    alt.Enums.CustomEventType.RESOURCE_STOP,
    "resourceStop",
    () => {
        return [];
    },
    true
);
