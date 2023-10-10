export class SharedPlayer {
    get flashlightActive() {
        return this.isFlashlightActive;
    }

    get headRot() {
        return this.headRotation;
    }

    toString() {
        return `Player{ id: ${this.id}, name: ${this.name} }`;
    }
}
