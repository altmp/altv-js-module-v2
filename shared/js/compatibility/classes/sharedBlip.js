export class SharedBlip {
    toString() {
        return `Blip{ name: ${this.name}, category: ${this.category} }`;
    }

    get isGlobal() {
        return this.global;
    }

    get size() {
        return this.scaleXY;
    }

    set size(value) {
        this.scaleXY = value;
    }

    get scale() {
        return this.scaleXY.x;
    }

    set scale(value) {
        this.scaleXY = { x: value, y: value };
    }

    get asMissionCreator() {
        return this.missionCreator;
    }

    set asMissionCreator(value) {
        this.missionCreator = value;
    }

    get isFriendly() {
        return this.friendly;
    }

    set isFriendly(value) {
        this.friendly = value;
    }
}
