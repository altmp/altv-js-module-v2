/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

const { Entity } = requireBinding("client/compatibility/classes/entity.js");
const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class WeaponObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [weapon, pos, rot, model, ammoCount, createDefaultComponents, scale, useStreaming, streamingDistance] = args;

        const instance = alt.WeaponObject.create({ weapon, pos, rot, model, ammoCount, createDefaultComponents, scale, useStreaming, streamingDistance });
        return extendAltEntityClass(instance, Entity, WorldObject, BaseObject);
    }

    get tintIndex() {
        return super.weaponTintIndex;
    }

    set tintIndex(value) {
        super.weaponTintIndex = value;
    }

    setComponentTintIndex(componentType, value) {
        super.getWeaponComponentTintIndex(componentType, value);
    }

    getComponentTintIndex(componentType) {
        return super.getWeaponComponentTintIndex(componentType);
    }

    giveComponent(componentType) {
        return super.giveWeaponComponent(componentType);
    }

    removeComponent(componentType) {
        return super.removeWeaponComponent(componentType);
    }

    static get all() {
        return alt.LocalObject.all.filter((obj) => obj.isWeaponObject);
    }

    static get count() {
        return alt.WeaponObject.all.length;
    }

    static getByScriptID(scriptID) {
        const obj = alt.LocalObject.getByScriptID(scriptID);

        if (!obj || !obj.isWeaponObject) return null;
        return obj;
    }

    static getByID(id) {
        const obj = alt.LocalObject.getByID(id);

        if (!obj || !obj.isWeaponObject) return null;
        return obj;
    }
}

cppBindings.registerCompatibilityExport("WeaponObject", WeaponObject);
