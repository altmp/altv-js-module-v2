const eventNameToEventType = {
    // Server
    serverStarted: alt.Enums.EventType.SERVER_STARTED,
    clientRequestObject: alt.Enums.EventType.CLIENT_REQUEST_OBJECT_EVENT,
    clientDeleteObject: alt.Enums.EventType.CLIENT_DELETE_OBJECT_EVENT,

    // Shared
    playerConnect: alt.Enums.EventType.PLAYER_CONNECT,
    playerDisconnect: alt.Enums.EventType.PLAYER_DISCONNECT,
    playerConnectDenied: alt.Enums.EventType.PLAYER_CONNECT_DENIED,
    playerSpawn: alt.Enums.EventType.PLAYER_SPAWN,

    connectionQueueAdd: alt.Enums.EventType.CONNECTION_QUEUE_ADD,
    connectionQueueRemove: alt.Enums.EventType.CONNECTION_QUEUE_REMOVE,

    anyResourceStart: alt.Enums.EventType.RESOURCE_START,
    anyResourceStop: alt.Enums.EventType.RESOURCE_STOP,
    anyResourceError: alt.Enums.EventType.RESOURCE_ERROR,

    serverScriptEvent: alt.Enums.EventType.SERVER_SCRIPT_EVENT,
    clientScriptEvent: alt.Enums.EventType.CLIENT_SCRIPT_EVENT,

    // metaChange? : alt.Enums.EventType.META_CHANGE, // Missing in v1 and v2 - doesn't seem to be called at all
    syncedMetaChange: alt.Enums.EventType.SYNCED_META_CHANGE,
    streamSyncedMetaChange: alt.Enums.EventType.STREAM_SYNCED_META_CHANGE,
    globalMetaChange: alt.Enums.EventType.GLOBAL_META_CHANGE,
    globalSyncedMetaChange: alt.Enums.EventType.GLOBAL_SYNCED_META_CHANGE,
    localMetaChange: alt.Enums.EventType.LOCAL_SYNCED_META_CHANGE,

    playerDamage: alt.Enums.EventType.PLAYER_DAMAGE,
    playerDeath: alt.Enums.EventType.PLAYER_DEATH,
    playerHeal: alt.Enums.EventType.PLAYER_HEAL,
    fireEvent: alt.Enums.EventType.FIRE_EVENT,
    explosionEvent: alt.Enums.EventType.EXPLOSION_EVENT,
    startProjectileEvent: alt.Enums.EventType.START_PROJECTILE_EVENT,
    weaponDamage: alt.Enums.EventType.WEAPON_DAMAGE_EVENT,
    vehicleDestroy: alt.Enums.EventType.VEHICLE_DESTROY,
    vehicleDamage: alt.Enums.EventType.VEHICLE_DAMAGE,

    requestSyncedScene: alt.Enums.EventType.REQUEST_SYNCED_SCENE,
    startSyncedScene: alt.Enums.EventType.START_SYNCED_SCENE,
    stopSyncedScene: alt.Enums.EventType.STOP_SYNCED_SCENE,
    updateSyncedScene: alt.Enums.EventType.UPDATE_SYNCED_SCENE,

    colshapeEvent: alt.Enums.EventType.COLSHAPE_EVENT,
    enteredVehicle: alt.Enums.EventType.PLAYER_ENTER_VEHICLE,
    enterVehicle: alt.Enums.EventType.PLAYER_START_ENTER_VEHICLE,
    playerEnteringVehicle: alt.Enums.EventType.PLAYER_ENTERING_VEHICLE,
    leftVehicle: alt.Enums.EventType.PLAYER_LEAVE_VEHICLE,
    leaveVehicle: alt.Enums.EventType.PLAYER_START_LEAVE_VEHICLE,
    changedVehicleSeat: alt.Enums.EventType.PLAYER_CHANGE_VEHICLE_SEAT,
    playerWeaponChange: alt.Enums.EventType.PLAYER_WEAPON_CHANGE,
    requestControl: alt.Enums.EventType.PLAYER_REQUEST_CONTROL,

    vehicleAttach: alt.Enums.EventType.VEHICLE_ATTACH,
    vehicleDetach: alt.Enums.EventType.VEHICLE_DETACH,
    vehicleHorn: alt.Enums.EventType.VEHICLE_HORN,
    vehicleSiren: alt.Enums.EventType.VEHICLE_SIREN,
    netOwnerChange: alt.Enums.EventType.NETOWNER_CHANGE,

    baseObjectCreate: alt.Enums.EventType.CREATE_BASE_OBJECT_EVENT,
    baseObjectRemove: alt.Enums.EventType.REMOVE_BASE_OBJECT_EVENT,

    // : alt.Enums.EventType.DATA_NODE_RECEIVED_EVENT, // Missing in v1 and v2

    consoleCommand: alt.Enums.EventType.CONSOLE_COMMAND_EVENT,

    animationChange: alt.Enums.EventType.PLAYER_CHANGE_ANIMATION_EVENT,

    playerInteriorChange: alt.Enums.EventType.PLAYER_CHANGE_INTERIOR_EVENT,

    playerWeaponShoot: alt.Enums.EventType.PLAYER_WEAPON_SHOOT_EVENT,
    playerBulletHit: alt.Enums.EventType.PLAYER_BULLET_HIT_EVENT,

    playerDimensionChange: alt.Enums.EventType.PLAYER_DIMENSION_CHANGE,

    // Client
    connectionComplete: alt.Enums.EventType.CONNECTION_COMPLETE,
    disconnect: alt.Enums.EventType.DISCONNECT_EVENT,
    webviewEvent: alt.Enums.EventType.WEB_VIEW_EVENT,
    keydown: alt.Enums.EventType.KEYBOARD_EVENT,
    keyup: alt.Enums.EventType.KEYBOARD_EVENT,
    gameEntityCreate: alt.Enums.EventType.GAME_ENTITY_CREATE,
    gameEntityDestroy: alt.Enums.EventType.GAME_ENTITY_DESTROY,
    webSocketEvent: alt.Enums.EventType.WEB_SOCKET_CLIENT_EVENT,
    audioEvent: alt.Enums.EventType.AUDIO_EVENT,
    taskChange: alt.Enums.EventType.TASK_CHANGE,
    spawned: alt.Enums.EventType.SPAWNED,
    rmlEvent: alt.Enums.EventType.RMLUI_EVENT,
    windowFocusChange: alt.Enums.EventType.WINDOW_FOCUS_CHANGE,
    windowResolutionChange: alt.Enums.EventType.WINDOW_RESOLUTION_CHANGE,
    entityHitEntity: alt.Enums.EventType.ENTITY_HIT_ENTITY,

    worldObjectPositionChange: alt.Enums.EventType.WORLD_OBJECT_POSITION_CHANGE,
    worldObjectStreamIn: alt.Enums.EventType.WORLD_OBJECT_STREAM_IN,
    worldObjectStreamOut: alt.Enums.EventType.WORLD_OBJECT_STREAM_OUT,

    voiceConnection: alt.Enums.EventType.VOICE_CONNECTION_EVENT
};

export function getEventNameFromEventType(eventType) {
    return Object.keys(eventNameToEventType).find((key) => eventNameToEventType[key] === eventType);
}

export function getEventTypeFromEventName(eventName) {
    return eventNameToEventType[eventName] ?? alt.Enums.EventType.NONE;
}

export const playerConnectEventConverter = {
    toNew: (...args) => ({ player: args[0] }),
    toOld: (args) => [args.player]
};
