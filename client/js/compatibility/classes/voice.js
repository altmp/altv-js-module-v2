/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class Voice extends alt.Voice {
    static get muteInput() {
        return alt.Voice.inputMuted;
    }

    static set muteInput(value) {
        alt.Voice.inputMuted = value;
    }

    static getAvailableInputDevices() {
        return alt.Voice.availableInputDevices;
    }
}

cppBindings.registerCompatibilityExport("Voice", Voice);
