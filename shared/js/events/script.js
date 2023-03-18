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
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE, "EntityCheckpointEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE, "EntityCheckpointLeave", true);

function getColShapeEventType(colShape, state) {
    const isCheckpoint = colShape instanceof alt.Checkpoint;
    if (!isCheckpoint && !state) return alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE;
    if (!isCheckpoint && state) return alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE;
    if (isCheckpoint && !state) return alt.Enums.CustomEventType.ENTITY_ENTER_CHECKPOINT;
    if (isCheckpoint && state) return alt.Enums.CustomEventType.ENTITY_LEAVE_CHECKPOINT;
}

alt.Events.onColShapeEvent(({ entity, colShape, state }) => {
    const eventType = getColShapeEventType(colShape, state);
    const data = {
        entity,
        colShape
    };

    Event.invoke(eventType, data, true);
});
