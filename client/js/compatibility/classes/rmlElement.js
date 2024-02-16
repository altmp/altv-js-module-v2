/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

class RmlElement extends alt.RmlElement {
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

cppBindings.registerCompatibilityExport("RmlElement", RmlElement);
