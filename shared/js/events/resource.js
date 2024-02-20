const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.RESOURCE_START, "AnyResourceStart");
Event.register(alt.Enums.EventType.RESOURCE_STOP, "AnyResourceStop");
Event.register(alt.Enums.EventType.RESOURCE_ERROR, "ResourceError");
Event.register(alt.Enums.CustomEventType.ERROR, "Error", true);
