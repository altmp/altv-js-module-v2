const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.CREATE_BASE_OBJECT_EVENT, "BaseObjectCreate");
Event.register(alt.Enums.EventType.REMOVE_BASE_OBJECT_EVENT, "BaseObjectRemove");
