/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("server/factory.js");

class ConnectionInfo extends alt.ConnectionInfo {
    get debug() {
        return super.isDebug;
    }

    get socialClubName() {
        return super.socialName;
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get passwordHash() {
        return super.passwordHash.toString();
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get hwidHash() {
        return super.hwidHash.toString();
    }

    // NOTE (xLuxy): In v1, value was returned as string for some reason
    get hwidExHash() {
        return super.hwidExHash.toString();
    }
}

alt.ConnectionInfo.setFactory(ConnectionInfo);
cppBindings.registerCompatibilityExport("ConnectionInfo", ConnectionInfo);
