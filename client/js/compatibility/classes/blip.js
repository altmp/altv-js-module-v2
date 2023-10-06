/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

class Blip extends alt.Blip {
    static count() {
        return alt.Blip.all.length;
    }

    set isGlobal(value) {
        super.global = value;
    }
}

alt.Factory.setBlipFactory(Blip);
cppBindings.registerCompatibilityExport("Blip", alt.Blip);
