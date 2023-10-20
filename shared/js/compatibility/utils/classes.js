/// <reference path="../../../../types/shared/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

export function extendAltEntityClass(baseInstance, ...classes) {
    if (baseInstance == null || typeof baseInstance !== "object") return;

    for (const class_ of classes) {
        assertIsType(class_, "function", `Expected class object, but got ${typeof class_}`);

        let currentClass = class_.prototype;
        while (currentClass !== Object.prototype) {
            for (const propKey of Object.getOwnPropertyNames(currentClass)) {
                if (propKey === "constructor") continue;

                if (baseInstance.hasOwnProperty(propKey)) {
                    const baseClassName = baseInstance.constructor.name;
                    const className = class_.name;

                    alt.log(`~lr~[Compatibility] Property '${propKey}' skipped in '${className}' - already in base class '${baseClassName}'.`);
                    continue;
                }

                const descriptor = Object.getOwnPropertyDescriptor(currentClass, propKey);
                if (descriptor) Object.defineProperty(baseInstance, propKey, descriptor);
            }

            currentClass = Object.getPrototypeOf(currentClass);
        }
    }

    return baseInstance;
}

export function overrideLazyProperty(instance, propertyName, value) {
    Object.defineProperty(instance, propertyName, {
        get() {
            return value;
        }
    });
}
