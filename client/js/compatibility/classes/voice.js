/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class Voice {
    static get muteInput() {
        return alt.Voice.inputMuted;
    }

    static set muteInput(value) {
        alt.Voice.inputMuted = value;
    }

    static get activityInputEnabled() {
        return alt.Voice.activityInputEnabled;
    }

    static set activityInputEnabled(state) {
        alt.Voice.activityInputEnabled = state;
    }

    static get activationLevel() {
        return alt.Voice.activationLevel;
    }

    static set activationLevel(value) {
        alt.Voice.activationLevel = value;
    }

    static get activationKey() {
        return alt.Voice.activationKey;
    }

    static get voiceControlsEnabled() {
        return alt.Voice.voiceControlsEnabled;
    }

    static get noiseSuppressionEnabled() {
        return alt.Voice.noiseSuppressionEnabled;
    }

    static set noiseSuppressionEnabled(state) {
        alt.Voice.noiseSuppressionEnabled = state;
    }

    static get inputDevice() {
        return alt.Voice.inputDevice;
    }

    static set inputDevice(value) {
        alt.Voice.inputDevice = value;
    }

    static getAvailableInputDevices() {
        return alt.Voice.availableInputDevices;
    }

    static toggleInput(state) {
        alt.Voice.toggleInput(state);
    }
}

cppBindings.registerCompatibilityExport("Voice", Voice);
