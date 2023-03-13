// clang-format off
const { Event } = requireBinding("shared/events.js");

// Entity all stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityAllMap = new Map();

function addAllGetter(class_, type) {
    const set = new Set();
    entityAllMap.set(type, set);
    class_.all = set;
}

alt.Events.onBaseObjectCreate(({ object }) => {
    if (object instanceof alt.Entity) {
        const all = entityAllMap.get(object.type);
        if (all) all.add(object);
        else alt.logError("INTERNAL ERROR: Entity type", object.type, "missing from entityAllMap");
    }
});

alt.Events.onBaseObjectRemove(({ object }) => {
    if (object instanceof alt.Entity) {
        const all = entityAllMap.get(object.type);
        if (all) all.delete(object);
        else alt.logError("INTERNAL ERROR: Entity type", object.type, "missing from entityAllMap");
    }
});

// Register all getters
addAllGetter(alt.Player, alt.Enums.BaseObjectType.PLAYER);
addAllGetter(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
