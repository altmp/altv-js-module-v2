const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_CONNECT, "PlayerConnect");
Event.register(alt.Enums.EventType.PLAYER_CONNECT_DENIED, "PlayerConnectDenied");
Event.register(alt.Enums.EventType.PLAYER_DISCONNECT, "PlayerDisconnect");
Event.register(alt.Enums.EventType.PLAYER_DAMAGE, "PlayerDamage");
Event.register(alt.Enums.EventType.PLAYER_DEATH, "PlayerDeath");
Event.register(alt.Enums.EventType.PLAYER_HEAL, "PlayerHeal");
Event.register(alt.Enums.EventType.PLAYER_REQUEST_CONTROL, "PlayerRequestControl");
Event.register(alt.Enums.EventType.PLAYER_CHANGE_INTERIOR_EVENT, "PlayerInteriorChange");
Event.register(alt.Enums.EventType.PLAYER_DIMENSION_CHANGE, "PlayerDimensionChange");
Event.register(alt.Enums.EventType.REQUEST_SYNCED_SCENE, "PlayerRequestSyncedScene");
Event.register(alt.Enums.EventType.START_SYNCED_SCENE, "PlayerStartSyncedScene");
Event.register(alt.Enums.EventType.STOP_SYNCED_SCENE, "PlayerStopSyncedScene");
Event.register(alt.Enums.EventType.UPDATE_SYNCED_SCENE, "PlayerUpdateSyncedScene");
