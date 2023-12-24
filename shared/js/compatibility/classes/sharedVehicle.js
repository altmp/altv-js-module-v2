export class SharedVehicle {
    get destroyed() {
        return this.isDestroyed;
    }

    get frontWheels() {
        return this.wheelVariation;
    }

    get rearWheels() {
        return this.rearWheelVariation;
    }

    setExtra(extraId, state) {
        this.toggleExtra(extraId, state);
    }

    getExtra(extraId) {
        return this.isExtraOn(extraId);
    }

    getAppearanceDataBase64() {
        return this.appearanceDataBase64;
    }

    get handbrakeActive() {
        return this.isHandbrakeActive;
    }

    get daylightOn() {
        return this.isDaylightOn;
    }

    get nightlightOn() {
        return this.isNightlightOn;
    }

    get roofClosed() {
        return this.roofState == 1;
    }

    get flamethrowerActive() {
        return this.isFlamethrowerActive;
    }

    get activeRadioStation() {
        return this.radioStationIndex;
    }

    getGamestateDataBase64() {
        return this.gameStateBase64;
    }

    doesWheelHasTire(wheelId) {
        return this.getWheelHasTire(wheelId);
    }

    getHealthDataBase64() {
        return this.healthDataBase64;
    }

    getDamageStatusBase64() {
        return this.damageDataBase64;
    }

    getScriptDataBase64() {
        return this.scriptDataBase64;
    }
}
