/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("../../../../shared/js/compatibility/utils/classes.js")} */
const { extendClassWithProperties, overrideLazyProperty } = requireBinding("shared/compatibility/utils/classes.js");

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

// NOTE(xLuxy): Store the original spawn method to call it later since we can't call it directly using super
//              and we need to override it
const originalSpawnMethod = alt.Player.prototype.spawn;

class Player {
    onCreate() {
        overrideLazyProperty(this, "socialID", this.socialID.toString());
        overrideLazyProperty(this, "hwidHash", this.hwidHash.toString());
        overrideLazyProperty(this, "hwidExHash", this.hwidHash.toString());
    }

    emitRpc(name, ...args) {
        return this.sendRPC(name, ...args);
    }

    hasLocalMeta(key) {
        return this.localMeta[key] !== undefined;
    }

    setLocalMeta(key, value) {
        this.localMeta[key] = value;
    }

    getLocalMeta(key) {
        return this.localMeta[key];
    }

    deleteLocalMeta(key) {
        delete this.localMeta[key];
    }

    getLocalMetaKeys() {
        return Object.keys(this.localMeta);
    }

    spawn(...args) {
        let pos = null;
        let delay = 0;

        if (args.length == 1 || args.length == 2) {
            // (model: number | string, pos: IVector3) overload
            if (typeof args[0] == "string" || typeof args[0] == "number") {
                this.model = args[0];
                pos = args[1];
                // (pos: IVector3, delay?: number) overload
            } else {
                [pos, delay] = args;
                delay ??= 0;
            }
            // (x: number, y: number, z: number, delay?: number) overload
        } else if (args.length == 3 || args.length == 4) {
            pos = { x: args[0], y: args[1], z: args[2] };
            delay = args[3];
        }

        originalSpawnMethod.call(this, pos, delay);
    }

    isEntityInStreamRange(entity) {
        return this.isEntityInStreamingRange(entity);
    }

    get currentInterior() {
        return this.interiorLocation;
    }

    getFaceFeatureScale(index) {
        return this.getFaceFeature(index);
    }

    setEyeColor(color) {
        this.eyeColor = color;
    }

    getEyeColor() {
        return this.eyeColor;
    }

    setHairColor(color) {
        this.hairColor = color;
    }

    getHairColor() {
        return this.hairColor;
    }

    setHairHighlightColor(color) {
        this.hairHighlightColor = color;
    }

    getHairHighlightColor() {
        return this.hairHighlightColor;
    }

    setHeadBlendData(shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix) {
        this.headBlendData = {
            shapeFirstID,
            shapeSecondID,
            shapeThirdID,
            skinFirstID,
            skinSecondID,
            skinThirdID,
            shapeMix,
            skinMix,
            thirdMix
        };
    }

    getHeadBlendData() {
        return this.headBlendData;
    }

    static get count() {
        return alt.Player.all.length;
    }
}

extendClassWithProperties(
    alt.Player,
    {
        whitelist: {
            nonStatic: ["spawn"]
        }
    },
    Player,
    SharedPlayer
);

cppBindings.registerCompatibilityExport("Player", alt.Player);
