requireBinding("shared/entity.js");
requireBinding("client/events/entity.js");

// Entity streamed-in stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityStreamedInMap = new Map(); // Stores a map of all streamed-in entities by type
const entityStreamedInSet = new Set(); // Stores a set of all streamed-in entities

/**
 * @param {unknown} class_
 * @param {number | number[]} types
 */
function addStreamedInGetter(class_, types) {
    if (!class_) return;
    if (!Array.isArray(types)) types = [types];

    const sets = [];
    for (const type of types) {
        const set = new Set();
        entityStreamedInMap.set(type, set);
        sets.push(set);
    }

    Object.defineProperties(class_, {
        streamedIn: {
            get: () => {
                if (class_.__streamedInDirty) {
                    class_.__streamedInCached = sets.flatMap((set) => Array.from(set));
                    class_.__streamedInDirty = false;
                }
                return class_.__streamedInCached;
            }
        },
        __streamedInDirty: {
            value: false,
            enumerable: false,
            writable: true,
            configurable: false
        },
        __streamedInCached: {
            value: [],
            enumerable: false,
            writable: true,
            configurable: false
        }
    });
}

function addEntityToStreamedIn(entity) {
    entityStreamedInSet.add(entity);
    const streamedIn = entityStreamedInMap.get(entity.type);
    streamedIn?.add(entity);
    entity.constructor.__streamedInDirty = true;
}
function removeEntityFromStreamedIn(entity) {
    entityStreamedInSet.delete(entity);
    const streamedIn = entityStreamedInMap.get(entity.type);
    streamedIn?.delete(entity);
    entity.constructor.__streamedInDirty = true;
}

alt.Events.onGameEntityCreate(({ entity }) => {
    addEntityToStreamedIn(entity);
});

alt.Events.onGameEntityDestroy(({ entity }) => {
    removeEntityFromStreamedIn(entity);
});

alt.Events.onWorldObjectStreamIn(({ object }) => {
    addEntityToStreamedIn(object);
});

alt.Events.onWorldObjectStreamOut(({ object }) => {
    removeEntityFromStreamedIn(object);
});

// Register streamedIn getters
Object.defineProperty(alt.Entity, "streamedIn", {
    get: () => Array.from(entityStreamedInSet)
});

addStreamedInGetter(alt.Player, alt.Enums.BaseObjectType.PLAYER);
addStreamedInGetter(alt.Vehicle, [alt.Enums.BaseObjectType.VEHICLE, alt.Enums.BaseObjectType.LOCAL_VEHICLE]);
addStreamedInGetter(alt.Ped, [alt.Enums.BaseObjectType.PED, alt.Enums.BaseObjectType.LOCAL_PED]);
addStreamedInGetter(alt.Object, [alt.Enums.BaseObjectType.OBJECT, alt.Enums.BaseObjectType.LOCAL_OBJECT]);
addStreamedInGetter(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);

// Add all streamed-in entities to the streamedIn sets
for (const entity of alt.Entity.all) {
    if (entity.scriptID !== 0) addEntityToStreamedIn(entity);
}
