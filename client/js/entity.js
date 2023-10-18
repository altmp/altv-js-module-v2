/** @type {typeof import("../../shared/js/entity.js")} */
const { addAllGetter } = requireBinding("shared/entity.js");

requireBinding("client/events/entity.js");
requireBinding("client/events/worldObject.js");

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

addAllGetter(alt.Audio, alt.Enums.BaseObjectType.AUDIO);
addAllGetter(alt.AudioFilter, alt.Enums.BaseObjectType.AUDIO_FILTER);
addAllGetter(alt.AudioOutputAttached, alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);
addAllGetter(alt.AudioOutputFrontend, alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);
addAllGetter(alt.AudioOutputWorld, alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);
addAllGetter(alt.RmlDocument, alt.Enums.BaseObjectType.RML_DOCUMENT);
addAllGetter(alt.TextLabel, alt.Enums.BaseObjectType.TEXT_LABEL);
addAllGetter(alt.WebSocketClient, alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);
addAllGetter(alt.WebView, alt.Enums.BaseObjectType.WEBVIEW);

addStreamedInGetter(alt.Player, [alt.Enums.BaseObjectType.PLAYER, alt.Enums.BaseObjectType.LOCAL_PLAYER]);
addStreamedInGetter(alt.Vehicle, [alt.Enums.BaseObjectType.VEHICLE, alt.Enums.BaseObjectType.LOCAL_VEHICLE]);
addStreamedInGetter(alt.Ped, [alt.Enums.BaseObjectType.PED, alt.Enums.BaseObjectType.LOCAL_PED]);
addStreamedInGetter(alt.Object, [alt.Enums.BaseObjectType.OBJECT, alt.Enums.BaseObjectType.LOCAL_OBJECT]);
addStreamedInGetter(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);

// Add all streamed-in entities to the streamedIn sets
for (const entity of alt.Entity.all) if (entity.streamedIn) addEntityToStreamedIn(entity);
for (const virtualEntity of alt.VirtualEntity.all) if (virtualEntity.isStreamedIn) addEntityToStreamedIn(virtualEntity);
