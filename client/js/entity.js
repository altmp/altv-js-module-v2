/** @type {typeof import("../../shared/js/entity.js")} */
const { addAllGetter, addEntityToAllWithType } = requireBinding("shared/entity.js");

requireBinding("client/events/entity.js");
requireBinding("client/events/worldObject.js");

// Entity streamed-in stores
/**
 * @type {Map<number, Set<unknown>>}
 */
const entityStreamedInMap = new Map(); // Stores a map of all streamed-in entities by type
const entityStreamedInSet = new Set(); // Stores a set of all streamed-in entities
const entityStreamedInStorageMap = new Map(); // Stores a map of what class stores what type in it's .streamedIn
let cachedEntityStreamedInArray = [];
let entityStreamedInSetDirty = false;

/**
 * @param {unknown} class_
 * @param {number} type
 */
function addStreamedInGetter(class_, type) {
    if (!class_) return;

    const set = new Set();
    entityStreamedInMap.set(type, set);
    entityStreamedInStorageMap.set(type, class_);

    Object.defineProperties(class_, {
        streamedIn: {
            get: () => {
                if (class_.__streamedInDirty) {
                    class_.__streamedInCached = Array.from(set);
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

function addEntityToStreamedIn(entity) {
    entityStreamedInSetDirty = true;
    entityStreamedInSet.add(entity);
    const all = entityStreamedInMap.get(entity.type);
    if (all) all.add(entity);
    const storageClass = entityStreamedInStorageMap.get(entity.type);
    if (storageClass) storageClass.__streamedInDirty = true;
}
function removeEntityFromStreamedIn(entity) {
    entityStreamedInSetDirty = true;
    entityStreamedInSet.delete(entity);
    const all = entityStreamedInMap.get(entity.type);
    if (all) all.delete(entity);
    const storageClass = entityStreamedInStorageMap.get(entity.type);
    if (storageClass) storageClass.__streamedInDirty = true;
}

// Register streamedIn getters
Object.defineProperty(alt.Entity, "streamedIn", {
    get: () => {
        if (entityStreamedInSetDirty) {
            cachedEntityStreamedInArray = Array.from(entityStreamedInSet);
            entityStreamedInSetDirty = false;
        }
        return cachedEntityStreamedInArray;
    }
});

addAllGetter(alt.LocalVehicle, alt.Enums.BaseObjectType.LOCAL_VEHICLE);
addAllGetter(alt.LocalPed, alt.Enums.BaseObjectType.LOCAL_PED);
addAllGetter(alt.LocalObject, alt.Enums.BaseObjectType.LOCAL_OBJECT);
addAllGetter(alt.Audio, alt.Enums.BaseObjectType.AUDIO);
addAllGetter(alt.AudioFilter, alt.Enums.BaseObjectType.AUDIO_FILTER);
addAllGetter(alt.AudioOutputAttached, alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);
addAllGetter(alt.AudioOutputFrontend, alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);
addAllGetter(alt.AudioOutputWorld, alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);
addAllGetter(alt.RmlDocument, alt.Enums.BaseObjectType.RML_DOCUMENT);
addAllGetter(alt.TextLabel, alt.Enums.BaseObjectType.TEXT_LABEL);
addAllGetter(alt.HttpClient, alt.Enums.BaseObjectType.HTTP_CLIENT);
addAllGetter(alt.WebSocketClient, alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);
addAllGetter(alt.WebView, alt.Enums.BaseObjectType.WEBVIEW);

addStreamedInGetter(alt.Player, alt.Enums.BaseObjectType.PLAYER);
addStreamedInGetter(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
addStreamedInGetter(alt.Ped, alt.Enums.BaseObjectType.PED);
addStreamedInGetter(alt.Object, alt.Enums.BaseObjectType.OBJECT);
addStreamedInGetter(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
addStreamedInGetter(alt.LocalVehicle, alt.Enums.BaseObjectType.LOCAL_VEHICLE);
addStreamedInGetter(alt.LocalPed, alt.Enums.BaseObjectType.LOCAL_PED);
addStreamedInGetter(alt.LocalObject, alt.Enums.BaseObjectType.LOCAL_OBJECT);

// Add all streamed-in entities to the streamedIn sets
for (const entity of alt.Entity.all) if (entity.isStreamedIn) addEntityToStreamedIn(entity);
for (const virtualEntity of cppBindings.getStreamedInVirtualEntities()) addEntityToStreamedIn(virtualEntity);
addEntityToAllWithType(alt.Player.local, alt.Enums.BaseObjectType.PLAYER);
