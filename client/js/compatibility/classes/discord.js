/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class Discord extends alt.Discord {
    static get currentUser() {
        return {
            id: alt.Discord.userID,
            name: alt.Discord.userName,
            discriminator: alt.Discord.discriminator,
            avatar: alt.Discord.avatar
        };
    }
}

cppBindings.registerCompatibilityExport("Discord", Discord);
