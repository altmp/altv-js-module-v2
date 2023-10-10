/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/factory.js");

const { SharedPlayer } = requireBinding("shared/compatibility/classes/sharedPlayer.js");

const { Entity } = requireBinding("server/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class Player extends alt.Player {
    constructor() {
        super();

        extendAltEntityClass(this, SharedPlayer, Entity, WorldObject, BaseObject);
    }

    emitRpc(name, ...args) {
        return super.sendRPC(name, ...args);
    }

    hasLocalMeta(key) {
        return key in super.localMeta;
    }

    setLocalMeta(key, value) {
        super.localMeta[key] = value;
    }

    getLocalMeta(key) {
        return super.localMeta[key];
    }

    deleteLocalMeta(key) {
        delete super.localMeta[key];
    }

    getLocalMetaKeys() {
        return Object.keys(super.localMeta);
    }

    spawn(...args) {
        let pos = null;
        let delay = 0;

        if (args.length == 1 || args.length == 2) {
            // (model: number | string, pos: IVector3) overload
            if (typeof args[0] == "string" || typeof args[0] == "number") {
                super.model = args[0];
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

        super.spawn(pos, delay);
    }

    isEntityInStreamRange(entity) {
        return super.isEntityInStreamingRange(entity);
    }

    get currentInterior() {
        return super.interiorLocation;
    }

    getFaceFeatureScale(index) {
        return super.getFaceFeature(index);
    }

    setEyeColor(color) {
        super.eyeColor = color;
    }

    getEyeColor() {
        return super.eyeColor;
    }

    setHairColor(color) {
        super.hairColor = color;
    }

    getHairColor() {
        return super.hairColor;
    }

    setHairHighlightColor(color) {
        super.hairHighlightColor = color;
    }

    getHairHighlightColor() {
        return super.hairHighlightColor;
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

    static get count() {
        return alt.Player.all.length;
    }
}

alt.Factory.setPlayerFactory(Player);
cppBindings.registerCompatibilityExport("Player", Player);
