/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.SERVER_STARTED, "serverStarted", () => {
    return [];
});

registerEventHandler(alt.Enums.EventType.CONNECTION_QUEUE_ADD, "connectionQueueAdd", ({ connectionInfo }) => {
    return [connectionInfo];
});

registerEventHandler(alt.Enums.EventType.CONNECTION_QUEUE_REMOVE, "connectionQueueRemove", ({ connectionInfo }) => {
    return [connectionInfo];
});
