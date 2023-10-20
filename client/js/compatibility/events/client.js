/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(
    alt.Enums.CustomEventType.KEY_UP,
    "keyup",
    ({ key }) => {
        return [key];
    },
    true
);

registerEventHandler(
    alt.Enums.CustomEventType.KEY_DOWN,
    "keydown",
    ({ key }) => {
        return [key];
    },
    true
);

// alt.Enums.EventType.WEB_VIEW_EVENT;             // Unimplemented in v1
// alt.Enums.EventType.WEB_SOCKET_CLIENT_EVENT;    // Unimplemented in v1
// alt.Enums.EventType.AUDIO_EVENT;                // Unimplemented in v1
// alt.Enums.EventType.RMLUI_EVENT;                // Unimplemented in v1

registerEventHandler(alt.Enums.EventType.WINDOW_FOCUS_CHANGE, "windowFocusChange", ({ state }) => {
    return [state];
});

registerEventHandler(alt.Enums.EventType.WINDOW_RESOLUTION_CHANGE, "windowResolutionChange", ({ oldResolution, newResolution }) => {
    return [oldResolution, newResolution];
});

registerEventHandler(alt.Enums.EventType.CONNECTION_COMPLETE, "connectionComplete", ({}) => {
    return [];
});

registerEventHandler(alt.Enums.EventType.DISCONNECT_EVENT, "disconnect", ({}) => {
    return [];
});

registerEventHandler(alt.Enums.EventType.SPAWNED, "spawned", ({}) => {
    return [];
});
