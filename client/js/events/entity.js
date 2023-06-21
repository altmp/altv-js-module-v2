const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.GAME_ENTITY_CREATE, "GameEntityCreate");
Event.register(alt.Enums.EventType.GAME_ENTITY_DESTROY, "GameEntityDestroy");
