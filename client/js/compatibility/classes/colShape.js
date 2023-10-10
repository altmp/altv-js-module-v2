/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/factory.js");

class Colshape extends alt.ColShape {
    //
}

alt.Factory.setColShapeFactory(Colshape);
cppBindings.registerCompatibilityExport("Colshape", Colshape);
