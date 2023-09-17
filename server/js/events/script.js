const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.EXPLOSION_EVENT, "Explosion");
Event.register(alt.Enums.EventType.FIRE_EVENT, "FireStart");
Event.register(alt.Enums.EventType.START_PROJECTILE_EVENT, "ProjectileStart");
Event.register(alt.Enums.EventType.GIVE_PED_SCRIPTED_TASK, "GivePedScriptedTask");
