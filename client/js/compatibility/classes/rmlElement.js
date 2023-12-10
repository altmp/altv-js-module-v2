/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/entity.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class RmlElement extends alt.RmlElement {
    constructor(...args) {
        super(...args);

        extendAltEntityClass(this, BaseObject);
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expected eventName to be a string, got ${typeof eventName}`);

        return super.listeners[eventName] ?? [];
    }

    get rmlId() {
        return super.rmlID;
    }

    set rmlId(value) {
        super.rmlID = value;
    }

    getClassList() {
        return super.classList;
    }

    getPseudoClassList(eventName) {
        return super.pseudoClassList;
    }

    getAttributes() {
        return super.attributes;
    }

    closest() {
        return super.getClosest();
    }
}

cppBindings.registerCompatibilityExport("RmlElement", alt.RmlElement);
