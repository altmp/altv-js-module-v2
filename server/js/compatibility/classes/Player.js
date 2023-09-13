/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

/** @type {typeof import("./Entity.js")} */
const { Entity } = requireBinding("server/compatibility/classes/Entity.js");

class Player extends Entity {
    constructor() {
        if (this.constructor === Player) {
            throw new Error("Cannot construct Player class");
        }
    }

    // https://github.com/altmp/altv-js-module/blob/132b88b9c347b7122eaa82349a63992b6ac4b33d/server/src/bindings/Player.cpp#L891
    get streamedEntities() {
        // TODO (xLuxy): Needs checking
        throw new Error("Not implemented");
    }

    static get count() {
        return alt.Player.all.length;
    }

    get flashlightActive() {
        return super.isFlashlightActive;
    }

    get headRot() {
        return super.headRotation;
    }

    get socialID() {
        return super.socialId;
    }

    get discordID() {
        return super.discordId;
    }

    get currentInterior() {
        return super.interiorLocation;
    }

    spawn(...args) {
        let pos;
        let delay = 0;

        if (args.length == 1 || args.length == 2) {
            super.model = args[0];
            pos = args[1];
        }

        if (info.Length() == 1 || info.Length() == 2) {
            // (model: number | string, pos: IVector3) overload
            if (typeof args[0] == "number" || typeof args[0] == "string") {
                super.model = args[0];
                pos = args[1];
            }
            // (pos: IVector3, delay?: number) overload
            else {
                pos = args[0];

                if (args.length == 2) {
                    delay = args[1];
                }
            }
        }
        // (x: number, y: number, z: number, delay?: number) overload
        else if (args.length == 3 || args.length == 4) {
            const [x, y, z] = args;
            if (args.length == 4) {
                delay = args[3];
            }
        }

        super.spawn(pos, delay);
    }

    setDlcClothes(...args) {
        const [dlc, component, drawable, texture, palette] = args;

        if (args.length == 4) {
            return super.setDlcClothes(component, drawable, texture, 2, dlc);
        } else if (args.length == 5) {
            return super.etDlcClothes(component, drawable, texture, palette, dlc);
        }
    }

    setDlcProp(dlc, component, drawable, texture) {
        return super.setDlcProps(component, drawable, texture, dlc);
    }

    getFaceFeatureScale(index) {
        return super.getFaceFeature(index);
    }

    setHeadBlendPaletteColor(id, red, green, blue) {
        return super.setHeadBlendPaletteColor(id, new alt.RGBA(red, green, blue));
    }

    setHeadBlendData(shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix) {
        super.headBlendData = {
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
        return super.headBlendData;
    }

    setEyeColor(eyeColor) {
        super.eyeColor = eyeColor;
    }

    getEyeColor() {
        return super.eyeColor;
    }

    setHairColor(hairColor) {
        super.hairColor = hairColor;
    }

    getHairColor() {
        return super.hairColor;
    }

    setHairHighlightColor(hairHighlightColor) {
        super.hairHighlightColor = hairHighlightColor;
    }

    getHairHighlightColor() {
        return super.hairHighlightColor;
    }

    getAmmoSpecialType(ammoHash) {
        return alt.Enums.AmmoSpecialType[super.getAmmoSpecialType(ammoHash)];
    }

    setLocalMeta(key, value) {
        super.localMeta[key] = value;
    }

    deleteLocalMeta(key) {
        delete super.localMeta[key];
    }

    getLocalMeta(key) {
        return super.localMeta[key];
    }

    hasLocalMeta(key) {
        return key in super.localMeta;
    }

    getLocalMetaKeys() {
        return Object.keys(super.localMeta);
    }

    setMeta(key, value) {
        super.meta[key] = value;
    }

    deleteMeta(key) {
        delete super.meta[key];
    }

    getMeta(key) {
        return super.meta[key];
    }

    hasMeta(key) {
        return key in super.meta;
    }

    setSyncedMeta(key, value) {
        super.syncedMeta[key] = value;
    }

    deleteSyncedMeta(key) {
        delete super.syncedMeta[key];
    }

    getSyncedMeta(key) {
        return super.syncedMeta[key];
    }

    hasSyncedMeta(key) {
        return key in super.syncedMeta;
    }

    setStreamSyncedMeta(key, value) {
        super.streamSyncedMeta[key] = value;
    }

    deleteStreamSyncedMeta(key) {
        delete super.streamSyncedMeta[key];
    }

    getStreamSyncedMeta(key) {
        return super.streamSyncedMeta[key];
    }

    hasStreamSyncedMeta(key) {
        return key in super.streamSyncedMeta;
    }
}

alt.Factory.setPlayerFactory(Player);
cppBindings.registerCompatibilityExport("Player", Player);
