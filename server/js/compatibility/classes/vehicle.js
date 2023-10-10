/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { SharedVehicle } = requireBinding("shared/compatibility/classes/sharedVehicle.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Vehicle extends alt.Vehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, ...rest] = args;
        const pos = rest.length <= 3 ? rest[0] : { x: rest[0], y: rest[1], z: rest[2] };
        const rot = rest.length <= 3 ? rest[1] : { x: rest[3], y: rest[4], z: rest[5] };
        const streamingDistance = rest.length === 3 ? rest[2] : rest[6];

        const instance = alt.Vehicle.create({ model, pos, rot, streamingDistance });
        return extendAltEntityClass(instance, SharedVehicle, Entity, WorldObject, BaseObject);
    }

    // TODO (xLuxy) Missing in v2
    get passengers() {
        alt.logWarning("Vehicle::passengers is not implemented yet.");
        return [];
    }

    setRearWheels(variation) {
        this.rearWheelVariation = variation;
    }

    setAppearanceDataBase64(data) {
        this.appearanceDataBase64 = data;
    }

    set engineOn(state) {
        this.isEngineOn = state;
    }

    set roofClosed(state) {
        this.roofState = state;
    }

    set activeRadioStation(stationIndex) {
        this.radioStationIndex = stationIndex;
    }

    get driftModeEnabled() {
        return this.driftMode;
    }

    set driftModeEnabled(state) {
        this.driftMode = state;
    }

    get hornActive() {
        return this.isHornActive;
    }

    setGamestateDataBase64(data) {
        this.gameStateBase64 = data;
    }

    setHealthDataBase64(data) {
        this.healthDataBase64 = data;
    }

    setDamageStatusBase64(data) {
        this.damageDataBase64 = data;
    }

    setScriptDataBase64(data) {
        this.scriptDataBase64 = data;
    }

    get trainEngineId() {
        return this.trainEngine;
    }

    setTrainEngineId(id) {
        this.trainEngine = id;
    }

    get isTrainEngine() {
        return this.hasTrainEngine;
    }

    set isTrainEngine(state) {
        this.hasTrainEngine = state;
    }

    get trainPassengerCarriages() {
        return this.hasTrainPassengerCarriages;
    }

    set trainPassengerCarriages(state) {
        this.hasTrainPassengerCarriages = state;
    }

    get trainLinkedToBackwardId() {
        return this.trainLinkedToBackward;
    }

    setTrainLinkedToBackwardId(entity) {
        this.trainLinkedToBackward = entity;
    }

    get trainLinkedToForwardId() {
        return this.trainLinkedToForward;
    }

    setTrainLinkedToForwardId(entity) {
        this.trainLinkedToForward = entity;
    }

    setSearchLightTo(state, spottedEntity) {
        return this.setSearchLight(state, spottedEntity);
    }

    static get count() {
        return alt.Vehicle.all.length;
    }
}

alt.Factory.setVehicleFactory(Vehicle);
cppBindings.registerCompatibilityExport("Vehicle", Vehicle);
