/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.VEHICLE_DESTROY, "vehicleDestroy", ({ vehicle }) => {
    return [vehicle];
});

registerEventHandler(alt.Enums.EventType.VEHICLE_ATTACH, "vehicleAttach", ({ vehicle, attachedVehicle }) => {
    return [vehicle, attachedVehicle];
});

registerEventHandler(alt.Enums.EventType.VEHICLE_DETACH, "vehicleDetach", ({ vehicle, detachedVehicle }) => {
    return [vehicle, detachedVehicle];
});

registerEventHandler(alt.Enums.EventType.VEHICLE_DAMAGE, "vehicleDamage", ({ vehicle, attacker, bodyHealthDamage, additionalBodyHealthDamage, engineHealthDamage, petrolTankDamage, weaponHash }) => {
    return [vehicle, attacker, bodyHealthDamage, additionalBodyHealthDamage, engineHealthDamage, petrolTankDamage, weaponHash];
});

registerEventHandler(alt.Enums.EventType.VEHICLE_SIREN, "vehicleSiren", ({ vehicle, state }) => {
    return [vehicle, state];
});

registerEventHandler(alt.Enums.EventType.VEHICLE_HORN, "vehicleHorn", ({ vehicle, state }) => {
    return [vehicle, state];
});
