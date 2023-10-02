/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.CLIENT_REQUEST_OBJECT_EVENT, "clientRequestObject", ({ player, model, pos }) => {
    return [player, model, pos];
});

registerEventHandler(alt.Enums.EventType.CLIENT_DELETE_OBJECT_EVENT, "clientDeleteObject", ({ player }) => {
    return [player];
});
