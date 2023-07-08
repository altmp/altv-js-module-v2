const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_CONNECT, "PlayerConnect");
Event.register(alt.Enums.EventType.PLAYER_CONNECT_DENIED, "PlayerConnectDenied");
Event.register(alt.Enums.EventType.PLAYER_DISCONNECT, "PlayerDisconnect");
Event.register(alt.Enums.EventType.PLAYER_DAMAGE, "PlayerDamage");
Event.register(alt.Enums.EventType.PLAYER_DEATH, "PlayerDeath");
Event.register(alt.Enums.EventType.PLAYER_REQUEST_CONTROL, "PlayerControlRequest");
Event.register(alt.Enums.EventType.PLAYER_CHANGE_INTERIOR_EVENT, "PlayerInteriorChange");
Event.register(alt.Enums.EventType.PLAYER_DIMENSION_CHANGE, "PlayerDimensionChange");
