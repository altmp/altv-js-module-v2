const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.COLSHAPE_EVENT, "ColShapeEvent");
Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, alt.isClient ? "RemoteScriptEvent" : "LocalScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, alt.isClient ? "LocalScriptEvent" : "RemoteScriptEvent");

// Custom ColShape events
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE, "EntityColShapeEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE, "EntityColShapeLeave", true);
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_CHECKPOINT, "EntityCheckpointEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_CHECKPOINT, "EntityCheckpointLeave", true);

function getColShapeEventType(colShape, state) {
    const isCheckpoint = colShape instanceof alt.Checkpoint;
    if (!isCheckpoint && state) return alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE;
    if (!isCheckpoint && !state) return alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE;
    if (isCheckpoint && state) return alt.Enums.CustomEventType.ENTITY_ENTER_CHECKPOINT;
    if (isCheckpoint && !state) return alt.Enums.CustomEventType.ENTITY_LEAVE_CHECKPOINT;
}

alt.Events.onColShapeEvent(({ entity, colShape, state }) => {
    const eventType = getColShapeEventType(colShape, state);
    const data = {
        entity,
        colShape
    };

    Event.invoke(eventType, data, true);
});
