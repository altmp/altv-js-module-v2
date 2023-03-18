const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "ServerScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "ClientScriptEvent");
// TODO: change to a better name
Event.register(alt.Enums.EventType.COLSHAPE_EVENT, "Colshape");
Event.register(alt.Enums.EventType.EXPLOSION_EVENT, "Explosion");
Event.register(alt.Enums.EventType.FIRE_EVENT, "FireStart");
Event.register(alt.Enums.EventType.START_PROJECTILE_EVENT, "ProjectileStart");
