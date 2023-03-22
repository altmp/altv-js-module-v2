// Entity all stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityAllMap = new Map(); // Stores a map of all entities by type
const entityAllSet = new Set(); // Stores a set of all entities

function addAllGetter(class_, type) {
    const set = new Set();
    entityAllMap.set(type, set);
    class_.all = set;
}

alt.Events.onBaseObjectCreate(({ object }) => {
    if (object instanceof alt.Entity) {
        entityAllSet.add(object);
        const all = entityAllMap.get(object.type);
        if (all) all.add(object);
        else alt.logError("INTERNAL ERROR: Entity type", object.type, "missing from entityAllMap");
    }
});

alt.Events.onBaseObjectRemove(({ object }) => {
    if (object instanceof alt.Entity) {
        entityAllSet.delete(object);
        const all = entityAllMap.get(object.type);
        if (all) all.delete(object);
        else alt.logError("INTERNAL ERROR: Entity type", object.type, "missing from entityAllMap");
    }
});

// Needed because base object events are called on next tick, and entities created from scripts
// should be immediately accessible in .all
export function addEntityToAll(entity) {
    entityAllSet.add(entity);
    const all = entityAllMap.get(entity.type);
    if (all) all.add(entity);
}

// Register all getters
alt.Entity.all = entityAllSet;

addAllGetter(alt.Player, alt.Enums.BaseObjectType.PLAYER);
addAllGetter(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
addAllGetter(alt.Ped, alt.Enums.BaseObjectType.PED);

// Register all entities that were created before this resource was loaded
const entities = cppBindings.getAllEntities();
for(const entity of entities) addEntityToAll(entity);
