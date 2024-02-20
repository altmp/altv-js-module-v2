const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.COLSHAPE_EVENT, "ColShapeEvent");
Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, alt.isClient ? "RemoteScriptEvent" : "LocalScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, alt.isClient ? "LocalScriptEvent" : "RemoteScriptEvent");
Event.register(alt.Enums.EventType.RESOURCE_START, "AnyResourceStart");
Event.register(alt.Enums.EventType.RESOURCE_STOP, "AnyResourceStop");

// Custom ColShape events
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_COLSHAPE, "EntityColShapeEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_COLSHAPE, "EntityColShapeLeave", true);
Event.register(alt.Enums.CustomEventType.ENTITY_ENTER_CHECKPOINT, "EntityCheckpointEnter", true);
Event.register(alt.Enums.CustomEventType.ENTITY_LEAVE_CHECKPOINT, "EntityCheckpointLeave", true);
Event.register(alt.Enums.CustomEventType.RESOURCE_START, "ResourceStart", true);
Event.register(alt.Enums.CustomEventType.RESOURCE_STOP, "ResourceStop", true);

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

alt.Events.onAnyResourceStart(({ resource }) => {
    if (resource.name !== alt.Resource.current.name) return;
    Event.invoke(alt.Enums.CustomEventType.RESOURCE_START, {}, true);
});

alt.Events.onAnyResourceStop(({ resource }) => {
    if (resource.name !== alt.Resource.current.name) return;
    Event.invoke(alt.Enums.CustomEventType.RESOURCE_STOP, {}, true);
});
