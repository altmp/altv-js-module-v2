const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SERVER_STARTED, "ServerStarted");
Event.register(alt.Enums.EventType.CONNECTION_QUEUE_ADD, "ConnectionQueueAdd");
Event.register(alt.Enums.EventType.CONNECTION_QUEUE_REMOVE, "ConnectionQueueRemove");
