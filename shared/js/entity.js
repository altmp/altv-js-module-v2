requireBinding("shared/events/entity.js");

// Entity all stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityAllMap = new Map(); // Stores a map of all entities by type
const entityAllSet = new Set(); // Stores a set of all entities
const entityAllStorageMap = new Map(); // Stores a map of what class stores what type in it's .all
let cachedEntityAllArray = [];
let entityAllSetDirty = false;

/**
 * @param {unknown} class_
 * @param {number} type
 */
export function addAllGetter(class_, type) {
    if (!class_) return;

    const set = new Set();
    entityAllMap.set(type, set);
    entityAllStorageMap.set(type, class_);

    Object.defineProperties(class_, {
        all: {
            get: () => {
                if (class_.__allDirty) {
                    class_.__allCached = Array.from(set);
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
    addEntityToAll(object);
});

alt.Events.onBaseObjectRemove(({ object }) => {
    removeEntityFromAll(object);
});

// TODO (xLuxy): Remove this once ScriptObject stuff is working as intended
alt.Events.onEvent((ctx) => {
    const eventName = ctx.customEvent ? alt.Enums.CustomEventType[ctx.eventType] : alt.Enums.EventType[ctx.eventType];
    alt.log(`~y~[JS Debug] Received event: ${eventName}:`, ctx);
});

export function addEntityToAll(entity) {
    addEntityToAllWithType(entity, entity.type);
}
export function removeEntityFromAll(entity) {
    entityAllSetDirty = true;
    entityAllSet.delete(entity);
    const all = entityAllMap.get(entity.type);
    if (all) all.delete(entity);
    const storageClass = entityAllStorageMap.get(entity.type);
    if (storageClass) storageClass.__allDirty = true;
}

export function addEntityToAllWithType(entity, type) {
    entityAllSetDirty = true;
    entityAllSet.add(entity);
    const all = entityAllMap.get(type);
    if (all) all.add(entity);
    const storageClass = entityAllStorageMap.get(type);
    if (storageClass) storageClass.__allDirty = true;
}

// Register all getters
Object.defineProperty(alt.Entity, "all", {
    get: () => {
        if (entityAllSetDirty) {
            cachedEntityAllArray = Array.from(entityAllSet);
            entityAllSetDirty = false;
        }
        return cachedEntityAllArray;
    }
});

addAllGetter(alt.Player, alt.Enums.BaseObjectType.PLAYER);
addAllGetter(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
addAllGetter(alt.Ped, alt.Enums.BaseObjectType.PED);
addAllGetter(alt.Blip, alt.Enums.BaseObjectType.BLIP);
addAllGetter(alt.Marker, alt.Enums.BaseObjectType.MARKER);
addAllGetter(alt.Object, alt.Enums.BaseObjectType.OBJECT);

addAllGetter(alt.Checkpoint, alt.Enums.BaseObjectType.CHECKPOINT);
addAllGetter(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);
addAllGetter(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);

// Register all entities that were created before this resource was loaded
const entities = cppBindings.getAllEntities();
for (const entity of entities) addEntityToAll(entity);
const virtualEntities = cppBindings.getAllVirtualEntities();
for (const virtualEntity of virtualEntities) addEntityToAll(virtualEntity);

// Needed because base object events are called on next tick, and entities created from scripts
// should be immediately accessible in .all
cppBindings.registerExport(cppBindings.BindingExport.ADD_ENTITY_TO_ALL, addEntityToAll);
