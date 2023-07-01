const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.WORLD_OBJECT_POSITION_CHANGE, "WorldObjectPositionChange");
Event.register(alt.Enums.EventType.WORLD_OBJECT_STREAM_IN, "WorldObjectStreamIn");
Event.register(alt.Enums.EventType.WORLD_OBJECT_STREAM_OUT, "WorldObjectStreamOut");
