/// <reference path="../../../../types/shared/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert, assertIsType } = requireBinding("shared/utils.js");

export function extendAltEntityClass(baseInstance, ...classes) {
    if (baseInstance == null || typeof baseInstance !== "object") return;

    for (const class_ of classes) {
        assertIsType(class_, "function", `Expected a class object as the first argument, but got ${typeof class_}`);

        for (const propKey of Object.getOwnPropertyNames(class_.prototype)) {
            if (propKey === "constructor") continue;

            const descriptor = Object.getOwnPropertyDescriptor(class_.prototype, propKey);
            if (descriptor) {
                Object.defineProperty(baseInstance, propKey, descriptor);
            }
        }
    }

    return baseInstance;
}
