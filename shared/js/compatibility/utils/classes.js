/// <reference path="../../../../types/shared/index.d.ts" />

// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

const blacklistedNonStaticProperties = ["constructor"];
const blacklistedStaticProperties = ["prototype", "length", "name", "caller", "arguments"];

function applyNonStaticProperties(baseClass, cls) {
    alt.log("applyNonStaticProperties", baseClass);

    let prot = cls.prototype;
    while (prot != Object.prototype) {
        for (const prop of Object.getOwnPropertyNames(prot)) {
            if (blacklistedNonStaticProperties.includes(prop) || baseClass[prop] || baseClass.prototype[prop]) {
                alt.log(`applyNonStaticProperties: Skipping property ${prop} (${prot.constructor.name})`);
                continue;
            }

            alt.log("applyNonStaticProperties", prop, prot);

            const property = Object.getOwnPropertyDescriptor(prot, prop);
            if (property) {
                Object.defineProperty(baseClass.prototype, prop, property);
            }
        }

        prot = Object.getPrototypeOf(prot);
    }
}

function applyStaticProperties(baseClass, cls) {
    alt.log("applyStaticProperties", baseClass, cls, Object.getOwnPropertyNames(cls));
    for (const propKey of Object.getOwnPropertyNames(cls)) {
        alt.log("applyStaticProperties 1", propKey);
        if (blacklistedStaticProperties.includes(propKey)) {
            alt.log("applyStaticProperties 2", propKey);
            continue;
        }
        if (baseClass[propKey] || baseClass.prototype[propKey]) {
            alt.log(`applyStaticProperties: Skipping property ${propKey} (${cls.name})`);
            continue;
        }

        const descriptor = Object.getOwnPropertyDescriptor(cls, propKey);
        if (!descriptor) continue;

        alt.log("applyStaticProperties", propKey, cls, cls[propKey], descriptor);

        if (typeof descriptor.get === "function") {
            Object.defineProperty(baseClass, propKey, {
                get: descriptor.get.bind(cls),
                enumerable: descriptor.enumerable,
                configurable: descriptor.configurable
            });
        } else {
            Object.defineProperty(baseClass, propKey, descriptor);
        }
    }
}

export function extendAltEntityClass(baseClass, ...classes) {
    assertIsType(baseClass, "function", `Expected class object, but got ${typeof baseClass}`);

    for (const cls of classes) {
        applyNonStaticProperties(baseClass, cls);
        applyStaticProperties(baseClass, cls);
    }

    return baseClass;
}

export function copyStaticAltEntityClassProperties(target, ...classes) {
    //
}

export function overrideLazyProperty(instance, propertyName, value) {
    Object.defineProperty(instance, propertyName, {
        get() {
            return value;
        }
    });
}
