/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class Blip extends alt.Blip {
    static count() {
        return alt.Blip.all.length;
    }
}

alt.Factory.setBlipFactory(Blip);
cppBindings.registerCompatibilityExport("Blip", alt.Blip);
