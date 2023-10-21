/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

class Colshape extends alt.ColShape {
    //
}

alt.ColShape.setFactory(Colshape);
cppBindings.registerCompatibilityExport("Colshape", Colshape);
