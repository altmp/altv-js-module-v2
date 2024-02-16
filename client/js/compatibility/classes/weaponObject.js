/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

class WeaponObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [weapon, pos, rot, model, ammoCount, createDefaultComponents, scale, useStreaming, streamingDistance] = args;

        return alt.WeaponObject.create({ weapon, pos, rot, model, ammoCount, createDefaultComponents, scale, useStreaming, streamingDistance });
    }

    get tintIndex() {
        return this.weaponTintIndex;
    }

    set tintIndex(value) {
        this.weaponTintIndex = value;
    }

    setComponentTintIndex(componentType, value) {
        this.getWeaponComponentTintIndex(componentType, value);
    }

    getComponentTintIndex(componentType) {
        return this.getWeaponComponentTintIndex(componentType);
    }

    giveComponent(componentType) {
        return this.giveWeaponComponent(componentType);
    }

    removeComponent(componentType) {
        return this.removeWeaponComponent(componentType);
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
