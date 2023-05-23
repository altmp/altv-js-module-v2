/// <reference path="./server/index.d.ts"/>
import * as alt from "@altv/server";

// Vehicle Checks...
alt.Vehicle.all;
const vehicle = alt.Vehicle.create({ model: "infernus", pos: new alt.Vector3(0, 0, 0), rot: new alt.Vector3(0, 0, 0) });

alt.Events.onPlayerConnect(({ player }) => {});

alt.Events.onPlayer("test", ({ player, args: [a, b, c] }) => {});

export class PlayerExtension extends alt.Player {
    doSomething(): number {
        return 1;
    }
}

alt.Events.onPlayer<PlayerExtension, [number, number, string]>("test", ({ player, args: [a, b, c] }) => {
    // Allows custom player interface, and args.
    player.doSomething(); // Should also show as valid...
});

alt.Events.onPlayer<[number, string]>("test", ({ player, args: [a, b] }) => {
    // Allows custom args first but player is optional.
});

alt.Events.onPlayer("test", ({ player, args: [a, b, c] }) => {
    // Allows default player, args.
    // All args are pushed as unknown.
});
