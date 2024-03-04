/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert } = requireBinding("shared/utils.js");

requireBinding("server/factory.js");

class VoiceChannel extends alt.VoiceChannel {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        assert(args.length === 2, "2 arguments expected");

        const [spatial, maxDistance] = args;
        return alt.VoiceChannel.create({ spatial, maxDistance });
    }

    isPlayerInChannel(player) {
        return this.hasPlayer(player);
    }
}

alt.VoiceChannel.setFactory(VoiceChannel);

cppBindings.registerCompatibilityExport("VoiceChannel", VoiceChannel);
