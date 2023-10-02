/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.WORLD_OBJECT_POSITION_CHANGE, "worldObjectPositionChange", ({ object, oldPos }) => {
    return [object, oldPos];
});

registerEventHandler(alt.Enums.EventType.WORLD_OBJECT_STREAM_IN, "worldObjectStreamIn", ({ object }) => {
    return [object];
});

registerEventHandler(alt.Enums.EventType.WORLD_OBJECT_STREAM_OUT, "worldObjectStreamOut", ({ object }) => {
    return [object];
});
