/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.META_CHANGE, "metaChange", ({ entity, key, oldValue, newValue }) => {
    return [entity, key, newValue, oldValue];
});

registerEventHandler(alt.Enums.EventType.LOCAL_SYNCED_META_CHANGE, "localMetaChange", ({ player, key, oldValue, newValue }) => {
    return [player, key, newValue, oldValue];
});

registerEventHandler(alt.Enums.EventType.STREAM_SYNCED_META_CHANGE, "streamSyncedMetaChange", ({ entity, key, oldValue, newValue }) => {
    return [entity, key, newValue, oldValue];
});

registerEventHandler(alt.Enums.EventType.GLOBAL_META_CHANGE, "globalMetaChange", ({ key, oldValue, newValue }) => {
    return [key, newValue, oldValue];
});

registerEventHandler(alt.Enums.EventType.GLOBAL_SYNCED_META_CHANGE, "globalSyncedMetaChange", ({ key, oldValue, newValue }) => {
    return [key, newValue, oldValue];
});
