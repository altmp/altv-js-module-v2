/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class HandlingData extends alt.HandlingData {
    static getForHandlingName(modelHash) {
        return alt.HandlingData.get(modelHash);
    }
}

cppBindings.registerCompatibilityExport("HandlingData", HandlingData);
