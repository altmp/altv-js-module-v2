/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

class Vehicle extends alt.Vehicle {
    // constructor(model | number, x, y, z, rx, ry, rz, streamingDistance?: number);
    // constructor(model | number, pos: shared.IVector3, rot: shared.IVector3, streamingDistance?: number);
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, ...rest] = args;
        const pos = rest.length <= 3 ? rest[0] : { x: rest[0], y: rest[1], z: rest[2] };
        const rot = rest.length <= 3 ? rest[1] : { x: rest[3], y: rest[4], z: rest[5] };
        const streamingDistance = rest.length === 3 ? rest[2] : rest[6];

        return alt.Vehicle.create({ model, pos, rot, streamingDistance });
    }

    static get count() {
        return alt.Vehicle.all.length;
    }

    get activeRadioStation() {
        return super.radioStationIndex;
    }

    set activeRadioStation(value) {
        super.radioStationIndex = value;
    }

    get darkness() {
        return super.specialDarkness;
    }

    set darkness(value) {
        super.specialDarkness = value;
    }

    get daylightOn() {
        return super.isDaylightOn;
    }

    get destroyed() {
        return super.isDestroyed;
    }

    get passengers() {
        throw new Error("Not implemented");
    }

    get engineOn() {
        return super.isEngineOn;
    }

    get flamethrowerActive() {
        return super.isFlamethrowerActive;
    }

    get handbrakeActive() {
        return super.isHandbrakeActive;
    }

    get nightlightOn() {
        return super.isNightlightOn;
    }

    get numberPlateIndex() {
        return super.numberplateIndex;
    }

    set numberPlateIndex(value) {
        super.numberplateIndex = value;
    }

    get numberPlateText() {
        return super.numberplateText;
    }

    set numberPlateText(value) {
        super.numberplateText = value;
    }

    get roofClosed() {
        return super.roofState === 1;
    }

    get frontWheels() {
        return super.wheelVariation;
    }

    get rearWheels() {
        return super.rearWheelVariation;
    }

    get driftModeEnabled() {
        return super.driftMode;
    }

    set driftModeEnabled(value) {
        super.driftMode = value;
    }

    getAppearanceDataBase64() {
        return super.appearanceDataBase64;
    }

    getDamageStatusBase64() {
        return super.damageDataBase64;
    }

    getExtra(extraId) {
        return super.isExtraOn(extraId);
    }

    getGamestateDataBase64() {
        return super.gameStateDataBase64;
    }

    getHealthDataBase64() {
        return super.healthDataBase64;
    }

    getScriptDataBase64() {
        return super.scriptDataBase64;
    }

    setAppearanceDataBase64(data) {
        super.appearanceDataBase64 = data;
    }

    setDamageStatusBase64(data) {
        super.damageDataBase64 = data;
    }

    setExtra(extraId, state) {
        super.toggleExtra(extraId, state);
    }

    setGamestateDataBase64(data) {
        super.gameStateDataBase64 = data;
    }

    setHealthDataBase64(data) {
        super.healthDataBase64 = data;
    }

    setScriptDataBase64(data) {
        super.scriptDataBase64 = data;
    }

    get trainEngineId() {
        return super.trainEngine;
    }

    setTrainEngineId(vehicle) {
        super.trainEngine = vehicle;
    }

    get trainLinkedToBackwardId() {
        return super.trainLinkedToBackward;
    }

    setTrainLinkedToBackwardId(vehicle) {
        super.trainLinkedToBackward = vehicle;
    }

    get trainLinkedToForwardId() {
        return super.trainLinkedToForward;
    }

    setTrainLinkedToForwardId(vehicle) {
        super.trainLinkedToForward = vehicle;
    }

    setSearchLightTo(entity, state) {
        super.setSearchLight(entity, state);
    }

    get boatAnchorActive() {
        return super.isBoatAnchorActive;
    }

    set boatAnchorActive(value) {
        super.isBoatAnchorActive = value;
    }

    get hornActive() {
        return super.isHornActive;
    }

    set hornActive(value) {
        super.isHornActive = value;
    }

    setMeta(key, value) {
        super.meta[key] = value;
    }

    deleteMeta(key) {
        delete super.meta[key];
    }

    getMeta(key) {
        return super.meta[key];
    }

    hasMeta(key) {
        return key in super.meta;
    }

    setSyncedMeta(key, value) {
        super.syncedMeta[key] = value;
    }

    deleteSyncedMeta(key) {
        delete super.syncedMeta[key];
    }

    getSyncedMeta(key) {
        return super.syncedMeta[key];
    }

    hasSyncedMeta(key) {
        return key in super.syncedMeta;
    }

    setStreamSyncedMeta(key, value) {
        super.streamSyncedMeta[key] = value;
    }

    deleteStreamSyncedMeta(key) {
        delete super.streamSyncedMeta[key];
    }

    getStreamSyncedMeta(key) {
        return super.streamSyncedMeta[key];
    }

    hasStreamSyncedMeta(key) {
        return key in super.streamSyncedMeta;
    }
}

alt.Factory.setVehicleFactory(Vehicle);
cppBindings.registerCompatibilityExport("Vehicle", Vehicle);
