const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "ServerScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "ClientScriptEvent");
Event.register(alt.Enums.EventType.COLSHAPE_EVENT, "ColShapeEvent");
Event.register(alt.Enums.EventType.EXPLOSION_EVENT, "Explosion");
Event.register(alt.Enums.EventType.FIRE_EVENT, "FireStart");
Event.register(alt.Enums.EventType.START_PROJECTILE_EVENT, "ProjectileStart");

// Custom ColShape events
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE, "EntityColShapeEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE, "EntityColShapeLeave", true);
alt.Events.onColShapeEvent(({ entity, colShape, state }) => {
    const type = state ? alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE : alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE;
    const data = {
        entity,
        colShape
    };
    Event.invoke(type, data, true);
});
