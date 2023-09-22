const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PED_DEATH, "PedDeath");
Event.register(alt.Enums.EventType.PED_DAMAGE, "PedDamage");
