const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.GAME_ENTITY_CREATE, "GameEntityCreate");
Event.register(alt.Enums.EventType.GAME_ENTITY_DESTROY, "GameEntityDestroy");
Event.register(alt.Enums.EventType.WEB_VIEW_EVENT, "WebViewEvent");
Event.register(alt.Enums.EventType.RMLUI_EVENT, "RmluiEvent");
