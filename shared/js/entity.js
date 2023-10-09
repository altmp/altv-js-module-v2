requireBinding("shared/events/entity.js");

// Entity all stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityAllMap = new Map(); // Stores a map of all entities by type
const entityAllSet = new Set(); // Stores a set of all entities

/**
 * @param {unknown} class_
 * @param {number | number[]} types
 */
export function addAllGetter(class_, types) {
    if (!class_) return;
    if (!Array.isArray(types)) types = [types];

    const sets = [];
    for (const type of types) {
        const set = new Set();
        entityAllMap.set(type, set);
        sets.push(set);
    }

    Object.defineProperties(class_, {
        all: {
            get: () => {
                if (class_.__allDirty) {
                    class_.__allCached = sets.flatMap((set) => Array.from(set));
                    class_.__allDirty = false;
                }
                return class_.__allCached;
            }
        },
        __allDirty: {
            value: false,
            enumerable: false,
            writable: true,
            configurable: false
        },
        __allCached: {
            value: [],
            enumerable: false,
            writable: true,
            configurable: false
        }
    });
}

alt.Events.onBaseObjectCreate(({ object }) => {
    if (object instanceof alt.Entity) addEntityToAll(object);
});

alt.Events.onBaseObjectRemove(({ object }) => {
    if (object instanceof alt.Entity) removeEntityFromAll(object);
});

// Needed because base object events are called on next tick, and entities created from scripts
// should be immediately accessible in .all
function addEntityToAll(entity) {
    entityAllSet.add(entity);
    const all = entityAllMap.get(entity.type);
    all?.add(entity);
    // Check if this is an extended class (for factory)
    const superClass = Object.getPrototypeOf(entity.constructor);
    if ("__allDirty" in superClass) superClass.__allDirty = true;
    else entity.constructor.__allDirty = true;
}
function removeEntityFromAll(entity) {
    entityAllSet.delete(entity);
    const all = entityAllMap.get(entity.type);
    all?.delete(entity);
    // Check if this is an extended class (for factory)
    const superClass = Object.getPrototypeOf(entity.constructor);
    if ("__allDirty" in superClass) superClass.__allDirty = true;
    else entity.constructor.__allDirty = true;
}
cppBindings.registerExport("entity:addEntityToAll", addEntityToAll);

// Register all getters
Object.defineProperty(alt.Entity, "all", {
    get: () => Array.from(entityAllSet)
});

addAllGetter(alt.Player, [alt.Enums.BaseObjectType.PLAYER, alt.Enums.BaseObjectType.LOCAL_PLAYER]);
addAllGetter(alt.Vehicle, [alt.Enums.BaseObjectType.VEHICLE, alt.Enums.BaseObjectType.LOCAL_VEHICLE]);
addAllGetter(alt.Ped, [alt.Enums.BaseObjectType.PED, alt.Enums.BaseObjectType.LOCAL_PED]);
addAllGetter(alt.Blip, alt.Enums.BaseObjectType.BLIP);
addAllGetter(alt.Marker, alt.Enums.BaseObjectType.MARKER);
addAllGetter(alt.Object, [alt.Enums.BaseObjectType.OBJECT, alt.Enums.BaseObjectType.LOCAL_OBJECT]);

addAllGetter(alt.Checkpoint, alt.Enums.BaseObjectType.CHECKPOINT);
addAllGetter(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);

// Register all entities that were created before this resource was loaded
const entities = cppBindings.getAllEntities();
for (const entity of entities) addEntityToAll(entity);
