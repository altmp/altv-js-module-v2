const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.CLIENT_DELETE_OBJECT_EVENT, "ClientObjectDelete");
Event.register(alt.Enums.EventType.CLIENT_REQUEST_OBJECT_EVENT, "ClientObjectRequest");
