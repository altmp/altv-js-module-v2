/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

class ConnectionInfo extends alt.ConnectionInfo {
    get debug() {
        return this.isDebug;
    }

    get socialClubName() {
        return this.socialName;
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get passwordHash() {
        return this.passwordHash.toString();
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get hwidHash() {
        return this.hwidHash.toString();
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get hwidExHash() {
        return this.hwidExHash.toString();
    }
}

cppBindings.registerCompatibilityExport("ConnectionInfo", ConnectionInfo);
