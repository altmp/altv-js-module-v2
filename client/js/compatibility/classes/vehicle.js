/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { SharedVehicle } = requireBinding("shared/compatibility/classes/sharedVehicle.js");

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Vehicle extends alt.Vehicle {
    constructor() {
        super();

        extendAltEntityClass(this, SharedVehicle, Entity, WorldObject, BaseObject);
    }

    toString() {
        return `Vehicle{ id: ${super.id}, model: ${super.model} }`;
    }

    get engineLight() {
        return super.engineLightState;
    }

    set engineLight(state) {
        super.engineLightState = state;
    }

    get absLight() {
        return super.absLightState;
    }

    set absLight(state) {
        super.absLightState = state;
    }

    get petrolLight() {
        return super.petrolLightState;
    }

    set petrolLight(state) {
        super.petrolLightState = state;
    }

    get oilLight() {
        return super.oilLightState;
    }

    set oilLight(state) {
        super.oilLightState = state;
    }

    get batteryLight() {
        return super.batteryLightState;
    }

    set batteryLight(state) {
        super.batteryLightState = state;
    }
}

alt.Factory.setVehicleFactory(Vehicle);
cppBindings.registerCompatibilityExport("Vehicle", Vehicle);
