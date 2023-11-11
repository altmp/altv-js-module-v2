function getClosestEntity(entities, options = {}) {
    if (!Array.isArray(entities) || !entities.length) return [null];

    const { pos = alt.Player.local.pos, range = Infinity } = options;

    let closestEntity = null;
    let closestDistance = range;

    for (const entity of entities) {
        if (typeof entity.pos !== "object") continue;

        const distance = entity.pos.distanceTo(pos);

        if (distance < closestDistance) {
            closestEntity = entity;
            closestDistance = distance;
        }
    }

    return [closestEntity, closestEntity ? closestDistance : undefined];
}

function getClosestEntityOfType(type, options = {}) {
    const { pos = alt.Player.local.pos, range = Infinity, checkpointType = undefined, colShapeType = undefined } = options;
    let { streamedInOnly = false } = options;
    const types = Array.isArray(type) ? type : [type];

    // NOTE (xLuxy): streamedIn doesn't exist on server-side
    if (alt.isServer) streamedInOnly = false;

    let entities = options.entities;
    if (!Array.isArray(entities)) {
        entities = streamedInOnly ? alt.Entity.streamedIn : alt.Entity.all;
        entities = entities.filter((entity) => types.includes(entity.type) && entity.pos.distanceTo(pos) <= range);

        // Check for checkpoint / colshape type specifically
        if (typeof checkpointType == "number" && types.includes(alt.Enums.BaseObjectType.CHECKPOINT)) {
            entities = entities.filter((entity) => entity.checkpointType == checkpointType);
        } else if (typeof colShapeType == "number" && types.includes(alt.Enums.BaseObjectType.COLSHAPE)) {
            entities = entities.filter((entity) => entity.colShapeType == colShapeType);
        }
    }

    return getClosestEntity(entities, options);
}

function getClosestPlayer(options = {}) {
    const types = options.localOnly ? alt.Enums.BaseObjectType.LOCAL_PLAYER : [alt.Enums.BaseObjectType.LOCAL_PLAYER, alt.Enums.BaseObjectType.PLAYER];

    return getClosestEntityOfType(types, options);
}

function getClosestPed(options = {}) {
    const types = options.localOnly ? alt.Enums.BaseObjectType.LOCAL_PED : [alt.Enums.BaseObjectType.LOCAL_PED, alt.Enums.BaseObjectType.PED];

    return getClosestEntityOfType(types, options);
}

function getClosestVehicle(options = {}) {
    const types = options.localOnly ? alt.Enums.BaseObjectType.LOCAL_VEHICLE : [alt.Enums.BaseObjectType.VEHICLE, alt.Enums.BaseObjectType.LOCAL_VEHICLE];

    return getClosestEntityOfType(types, options);
}

function getClosestObject(options = {}) {
    const types = options.localOnly ? alt.Enums.BaseObjectType.LOCAL_OBJECT : [alt.Enums.BaseObjectType.OBJECT, alt.Enums.BaseObjectType.LOCAL_OBJECT];

    return getClosestEntityOfType(types, options);
}

// checkpointType
function getClosestCheckpoint(options = {}) {
    return getClosestEntityOfType(alt.Enums.BaseObjectType.CHECKPOINT, options);
}

// colShapeType
function getClosestColShape(options = {}) {
    return getClosestEntityOfType(alt.Enums.BaseObjectType.COLSHAPE, options);
}

function getClosestVirtualEntity(options = {}) {
    return getClosestEntityOfType(alt.Enums.BaseObjectType.VIRTUAL_ENTITY, options);
}

alt.Utils.getClosestEntity = getClosestEntity;
alt.Utils.getClosestEntityOfType = getClosestEntityOfType;

alt.Utils.getClosestPlayer = getClosestPlayer;
alt.Utils.getClosestPed = getClosestPed;
alt.Utils.getClosestVehicle = getClosestVehicle;
alt.Utils.getClosestObject = getClosestObject;
alt.Utils.getClosestCheckpoint = getClosestCheckpoint;
alt.Utils.getClosestColShape = getClosestColShape;
alt.Utils.getClosestVirtualEntity = getClosestVirtualEntity;
