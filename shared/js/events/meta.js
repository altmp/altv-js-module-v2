const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.META_CHANGE, "MetaChange");
Event.register(alt.Enums.EventType.LOCAL_SYNCED_META_CHANGE, "LocalMetaChange");
Event.register(alt.Enums.EventType.STREAM_SYNCED_META_CHANGE, "StreamSyncedMetaChange");
Event.register(alt.Enums.EventType.GLOBAL_META_CHANGE, "GlobalMetaChange");
Event.register(alt.Enums.EventType.GLOBAL_SYNCED_META_CHANGE, "GlobalSyncedMetaChange");
