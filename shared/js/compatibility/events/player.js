/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.PLAYER_CHANGE_ANIMATION_EVENT, "playerAnimationChange", ({ player, oldAnimDict, newAnimDict, oldAnimName, newAnimName }) => {
    return [player, oldAnimDict, newAnimDict, oldAnimName, newAnimName];
});

registerEventHandler(alt.Enums.PLAYER_ENTER_VEHICLE, "playerEnteredVehicle", ({ player, vehicle, seat }) => {
    return [player, vehicle, seat];
});

registerEventHandler(alt.Enums.EventType.PLAYER_ENTERING_VEHICLE, "playerEnteringVehicle", ({ player, vehicle, seat }) => {
    return [player, vehicle, seat];
});

registerEventHandler(alt.Enums.EventType.PLAYER_LEAVE_VEHICLE, "playerLeftVehicle", ({ player, vehicle, seat }) => {
    return [player, vehicle, seat];
});

registerEventHandler(alt.Enums.EventType.PLAYER_CHANGE_VEHICLE_SEAT, "playerChangedVehicleSeat", ({ player, vehicle, oldSeat, newSeat }) => {
    return [player, vehicle, oldSeat, newSeat];
});

registerEventHandler(alt.Enums.EventType.PLAYER_START_TALKING, "playerStartTalking", ({ player }) => {
    return [player];
});

registerEventHandler(alt.Enums.EventType.PLAYER_STOP_TALKING, "playerStopTalking", ({ player }) => {
    return [player];
});
