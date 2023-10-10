/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class LocalPlayer extends alt.LocalPlayer {
    // NOTE (xLuxy): If we export this class, instanceof is broken UNLESS factory is used
}

cppBindings.registerCompatibilityExport("LocalPlayer", LocalPlayer);
