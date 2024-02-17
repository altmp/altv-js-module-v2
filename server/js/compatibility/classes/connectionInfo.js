/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties, overrideLazyProperty } = requireBinding("shared/compatibility/utils/classes.js");

class ConnectionInfo {
    onCreate() {
        overrideLazyProperty(this, "socialID", this.socialID.toString());
        overrideLazyProperty(this, "discordUserID", this.discordUserID.toString());

        overrideLazyProperty(this, "hwidHash", this.hwidHash.toString());
        overrideLazyProperty(this, "hwidExHash", this.hwidExHash.toString());
    }

    get isDebug() {
        return this.debug;
    }
}

extendClassWithProperties(alt.ConnectionInfo, null, ConnectionInfo);

cppBindings.registerCompatibilityExport("ConnectionInfo", alt.ConnectionInfo);
