/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

// requireBinding("client/entity.js");

export class AudioOutput extends alt.AudioOutput {
    //
}

cppBindings.registerCompatibilityExport("AudioOutput", AudioOutput);
