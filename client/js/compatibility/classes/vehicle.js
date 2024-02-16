/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

const { SharedVehicle } = requireBinding("shared/compatibility/classes/sharedVehicle.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Vehicle {
    toString() {
        return `Vehicle{ id: ${this.id}, model: ${this.model} }`;
    }

    get engineLight() {
        return this.engineLightState;
    }

    set engineLight(state) {
        this.engineLightState = state;
    }

    get absLight() {
        return this.absLightState;
    }

    set absLight(state) {
        this.absLightState = state;
    }

    get petrolLight() {
        return this.petrolLightState;
    }

    set petrolLight(state) {
        this.petrolLightState = state;
    }

    get oilLight() {
        return this.oilLightState;
    }

    set oilLight(state) {
        this.oilLightState = state;
    }

    get batteryLight() {
        return this.batteryLightState;
    }

    set batteryLight(state) {
        this.batteryLightState = state;
    }

    static get count() {
        return alt.Vehicle.all.length;
    }
}

extendAltEntityClass(alt.Vehicle, Vehicle, SharedVehicle);

cppBindings.registerCompatibilityExport("Vehicle", alt.Vehicle);
