/// <reference path="../../../../types/shared/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType, assertIsObject } = requireBinding("shared/utils.js");

export function extendAltEntityClass(baseInstance, ...classes) {
    assertIsObject(baseInstance, `Expected object, but got ${typeof baseInstance}`);

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

export function copyStaticAltEntityClassProperties(target, ...classes) {
    assertIsType(target, "function", `Expected class object, but got ${typeof target}`);

    for (const class_ of classes) {
        assertIsType(class_, "function", `Expected class object, but got ${typeof class_}`);

        for (const propKey of Object.getOwnPropertyNames(class_)) {
            if (["prototype", "length", "name", "caller", "arguments"].includes(propKey)) {
                continue;
            }

            if (target.hasOwnProperty(propKey)) {
                const baseClassName = target.constructor.name;
                const className = class_.name;

                alt.log(`~lr~[Compatibility] Property '${propKey}' skipped in '${className}' - already in base class '${baseClassName}'.`);
                continue;
            }

            const descriptor = Object.getOwnPropertyDescriptor(class_, propKey);

            if (!descriptor) continue;

            if (typeof descriptor.get === "function") {
                Object.defineProperty(target, propKey, {
                    get: descriptor.get.bind(class_),
                    enumerable: descriptor.enumerable,
                    configurable: descriptor.configurable
                });
            } else {
                Object.defineProperty(target, propKey, descriptor);
            }
        }
    }
}

export function overrideLazyProperty(instance, propertyName, value) {
    Object.defineProperty(instance, propertyName, {
        get() {
            return value;
        }
    });
}
