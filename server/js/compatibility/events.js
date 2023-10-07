/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../../../shared/js/compatibility/utils/events.js")} */
const { getEventTypeFromName, getEventArgumentConverter, isCustomEvent } = requireBinding("shared/compatibility/utils/events.js");

function emitClient(player, eventName, ...args) {
    if (!(player instanceof alt.Player) || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayers(player, eventName, ...args);
        return;
    }

    player.emit(eventName, ...args);
}

function emitClientRaw(player, eventName, ...args) {
    if (!(player instanceof alt.Player) || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayersRaw(player, eventName, ...args);
        return;
    }

    player.emitRaw(eventName, ...args);
}

function emitClientUnreliable(player, eventName, ...args) {
    if (!(player instanceof alt.Player) || !Array.isArray(player)) return;

    if (Array.isArray(player)) {
        alt.Events.emitPlayersUnreliable(player, eventName, ...args);
        return;
    }

    player.emitUnreliable(eventName, ...args);
}

cppBindings.registerCompatibilityExport("emitClient", emitClient);
cppBindings.registerCompatibilityExport("emitClientRaw", emitClientRaw);
cppBindings.registerCompatibilityExport("emitClientUnreliable", emitClientUnreliable);

cppBindings.registerCompatibilityExport("emitAllClients", alt.Events.emitAllPlayers);
cppBindings.registerCompatibilityExport("emitAllClientsRaw", alt.Events.emitAllPlayersRaw);
cppBindings.registerCompatibilityExport("emitAllClientsUnreliable", alt.Events.emitAllPlayersUnreliableRaw);

// TODO (xLuxy)
// export function offClient(eventName: string, listener: (player: Player, ...args: any[]) => void): void;
// export function offClient(listener: (eventName: string, ...args: any[]) => void): void;
// export function onClient(listener: (eventName: string, player: Player, ...args: any[]) => void): void;
// export function onceClient(listener: (eventName: string, player: Player, ...args: any[]) => void): void;
