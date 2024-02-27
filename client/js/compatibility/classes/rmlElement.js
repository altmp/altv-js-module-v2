/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

class RmlElement extends alt.RmlElement {
    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expected eventName to be a string, got ${typeof eventName}`);

        return this.listeners[eventName] ?? [];
    }

    get rmlId() {
        return this.rmlID;
    }

    set rmlId(value) {
        this.rmlID = value;
    }

    get isOwned() {
        return this.owned;
    }

    get isVisible() {
        return this.visible;
    }

    get isPointWithinElement() {
        return this.pointWithinElement;
    }

    getClassList() {
        return this.classList;
    }

    getPseudoClassList(eventName) {
        return this.pseudoClassList;
    }

    getAttributes() {
        return this.attributes;
    }

    closest() {
        return this.getClosest();
    }
}

cppBindings.registerCompatibilityExport("RmlElement", RmlElement);
