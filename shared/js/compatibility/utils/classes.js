/// <reference path="../../../../types/shared/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

export function extendAltEntityClass(baseInstance, ...classes) {
    if (baseInstance == null || typeof baseInstance !== "object") return;

    for (const class_ of classes) {
        assertIsType(class_, "function", `Expected class object, but got ${typeof class_}`);

        for (const propKey of Object.getOwnPropertyNames(class_.prototype)) {
            if (propKey === "constructor") continue;

            // TODO (xLuxy): We might want to override shared properties?
            if (baseInstance.hasOwnProperty(propKey)) {
                const baseClassName = baseInstance.constructor.name;
                const className = class_.name;

                alt.log(`~lr~[Compatibility] Property '${propKey}' skipped in '${className}' - already in base class '${baseClassName}'.`);
                continue;
            }

            const descriptor = Object.getOwnPropertyDescriptor(class_.prototype, propKey);
            if (descriptor) Object.defineProperty(baseInstance, propKey, descriptor);
        }
    }

    return baseInstance;
}
