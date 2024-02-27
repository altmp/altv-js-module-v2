/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class LocalObject extends alt.LocalObject {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance] = args;

        return alt.LocalObject.create({ model, pos, rot, noOffset, dynamic, useStreaming, streamingDistance });
    }

    toString() {
        return `Object{ model: ${this.model}, scriptID: ${this.scriptID} }`;
    }

    static get count() {
        return alt.LocalObject.all.length;
    }

    get isCollisionEnabled() {
        return this.collisionEnabled;
    }

    get isStreamedIn() {
        return this.streamedIn;
    }

    get isWorldObject() {
        return this.worldObject;
    }

    get isWeaponObject() {
        return this.weaponObject;
    }

    attachToEntity(...args) {
        return this.attachTo(...args);
    }
}

alt.LocalObject.setFactory(LocalObject);

cppBindings.registerCompatibilityExport("LocalObject", LocalObject);
