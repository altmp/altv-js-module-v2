/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class Colshape extends alt.ColShape {
    //
}

alt.ColShape.setFactory(Colshape);
cppBindings.registerCompatibilityExport("Colshape", Colshape);
