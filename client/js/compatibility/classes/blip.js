/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class Blip extends alt.Blip {
    static get count() {
        return alt.Blip.all.length;
    }
}

alt.Blip.setFactory(Blip);
cppBindings.registerCompatibilityExport("Blip", alt.Blip);
