const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.RESOURCE_START, "ResourceStart");
Event.register(alt.Enums.EventType.RESOURCE_STOP, "ResourceStop");
Event.register(alt.Enums.EventType.RESOURCE_ERROR, "ResourceError");
Event.register(alt.Enums.CustomEventType.ERROR, "Error", true);
