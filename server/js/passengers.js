/// <reference path="../../types/shared/index.d.ts" />
/// <reference path="../../types/server/index.d.ts" />
/// <reference path="../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/events/entity.js");
requireBinding("shared/events/player.js");

const passengerMap = new Map();

alt.Events.onPlayerEnteredVehicle(({ player, vehicle, seat }) => {
    const passengers = passengerMap.get(vehicle) ?? new Map();

    passengers.set(seat, player);
    passengerMap.set(vehicle, passengers);
});

alt.Events.onPlayerLeftVehicle(({ vehicle, seat }) => {
    if (!passengerMap.has(vehicle)) return;

    const passengers = passengerMap.get(vehicle);
    passengers.delete(seat);

    if (!passengers.size) passengerMap.delete(vehicle);
});

alt.Events.onPlayerVehicleSeatChange(({ player, vehicle, oldSeat, newSeat }) => {
    if (!passengerMap.has(vehicle)) return;

    const passengers = passengerMap.get(vehicle);
    passengers.delete(oldSeat);
    passengers.set(newSeat, player);
});

alt.Events.onBaseObjectRemove(({ object, type }) => {
    if (type != alt.Enums.BaseObjectType.VEHICLE) return;

    passengerMap.delete(object);
});

alt.Events.onPlayerDisconnect(({ player }) => {
    if (!player.isInVehicle) return;

    const { vehicle, seat } = player;

    if (!passengerMap.has(vehicle)) return;

    const passengers = passengerMap.get(vehicle);
    passengers.delete(seat);

    if (!passengers.size) passengerMap.delete(vehicle);
});

Object.defineProperty(alt.Vehicle.prototype, "passengers", {
    get() {
        const passengersMap = passengerMap.get(this) || new Map();
        return Object.freeze(Object.fromEntries(passengersMap.entries()));
    }
});
