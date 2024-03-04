/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties } = requireBinding("shared/compatibility/utils/classes.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert, assertIsOneOfType } = requireBinding("shared/utils.js");

const { SharedVehicle } = requireBinding("shared/compatibility/classes/sharedVehicle.js");

requireBinding("server/factory.js");

class Vehicle extends alt.Vehicle {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length >= 3 && args.length <= 8, "Minimum 3, maximum 8 arguments expected");
        assertIsOneOfType(args[0], ["string", "number"], "string or number expected");

        const [model, ...rest] = args;
        const pos = rest.length <= 3 ? rest[0] : { x: rest[0], y: rest[1], z: rest[2] };
        const rot = rest.length <= 3 ? rest[1] : { x: rest[3], y: rest[4], z: rest[5] };
        const streamingDistance = rest.length === 3 ? rest[2] : rest[6];

        return alt.Vehicle.create({ model, pos, rot, streamingDistance });
    }

    setRearWheels(variation) {
        this.rearWheelVariation = variation;
    }

    setAppearanceDataBase64(data) {
        this.appearanceDataBase64 = data;
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

extendClassWithProperties(Vehicle, null, SharedVehicle);

alt.Vehicle.setFactory(Vehicle);

cppBindings.registerCompatibilityExport("Vehicle", Vehicle);
