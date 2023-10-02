/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/entity.js");

class Vehicle extends alt.Vehicle {
    static get count() {
        return alt.Vehicle.all.length;
    }

    get engineOn() {
        return super.isEngineOn;
    }

    get handbrakeActive() {
        return super.isHandbrakeActive;
    }

    get sirenActive() {
        return super.isSirenActive;
    }

    get manualEngineControl() {
        return super.isManulEngineControl;
    }

    get engineLight() {
        return super.engineLightState;
    }

    set engineLight(value) {
        super.engineLightState = value;
    }

    get absLight() {
        return super.absLightState;
    }

    set absLight(value) {
        super.absLightState = value;
    }

    get petrolLight() {
        return super.petrolLightState;
    }

    set petrolLight(value) {
        super.petrolLightState = value;
    }

    get oilLight() {
        return super.oilLightState;
    }

    set oilLight(value) {
        super.oilLightState = value;
    }

    get batteryLight() {
        return super.batteryLightState;
    }

    set batteryLight(value) {
        super.batteryLightState = value;
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

    getSyncedMeta(key) {
        return super.syncedMeta[key];
    }

    hasSyncedMeta(key) {
        return key in super.syncedMeta;
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
