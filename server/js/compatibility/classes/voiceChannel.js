/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendAltEntityClass, copyStaticAltEntityClassProperties } = requireBinding("shared/compatibility/utils/classes.js");

class VoiceChannel extends alt.VoiceChannel {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) {
            super();
            return extendAltEntityClass(this, BaseObject);
        }

        const [spatial, maxDistance] = args;
        const instance = alt.VoiceChannel.create({ spatial, maxDistance });
        return extendAltEntityClass(instance, BaseObject);
    }

    isPlayerInChannel(player) {
        return super.hasPlayer(player);
    }
}

copyStaticAltEntityClassProperties(alt.VoiceChannel, VoiceChannel, BaseObject);

alt.VoiceChannel.setFactory(VoiceChannel);
cppBindings.registerCompatibilityExport("VoiceChannel", VoiceChannel);
