/// <reference path="../../../../types/shared/index.d.ts" />
// import * as alt from "@altv/shared";

requireBinding("shared/logging.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

const defaultOptions = {
    verbose: false,

    blacklist: {
        nonStatic: ["constructor"],
        static: ["prototype", "length", "name", "caller", "arguments"]
    },

    whitelist: {
        nonStatic: [],
        static: []
    }
};

function applyNonStaticProperties(baseClass, cls, options) {
    let prot = cls.prototype;
    while (prot !== Object.prototype) {
        for (const prop of Object.getOwnPropertyNames(prot)) {
            const baseDescriptor = Object.getOwnPropertyDescriptor(baseClass.prototype, prop);
            const newDescriptor = Object.getOwnPropertyDescriptor(prot, prop);

            const isBlacklisted = options.blacklist.nonStatic.includes(prop);
            const isWhitelisted = options.whitelist.nonStatic.includes(prop);
            const canBeMerged = !isBlacklisted || isWhitelisted;

            if (canBeMerged && newDescriptor) {
                let mergedDescriptor = {};

                if (baseDescriptor) {
                    mergedDescriptor = { ...baseDescriptor };
                }

                ["get", "set", "value", "writeable"].forEach((key) => {
                    if (key in newDescriptor && !mergedDescriptor[key]) {
                        if (options.verbose) {
                            alt.log(`~ly~[JS] ~lr~Merged ${key} for ${prop} from ${prot.constructor.name} to ${baseClass.name}`);
                        }
                        mergedDescriptor[key] = newDescriptor[key];
                    }
                });

                Object.defineProperty(baseClass.prototype, prop, mergedDescriptor);

                if (options.verbose) {
                    const action = baseDescriptor ? "Merged" : "Applied";
                    alt.log(`~ly~[JS] ~lb~${action} non-static property ${prop} from ${prot.constructor.name} to ${baseClass.name}`);
                }
            }
        }

        prot = Object.getPrototypeOf(prot);
    }
}

function applyStaticProperties(baseClass, cls, options) {
    for (const propKey of Object.getOwnPropertyNames(cls)) {
        const doesPropertyExist = propKey in baseClass || propKey in baseClass.prototype;
        const canBeOverriden = !options.blacklist.static.includes(propKey) || options.whitelist.static.includes(propKey);

        if (doesPropertyExist && !canBeOverriden) {
            if (options.verbose) {
                const reason = !canBeOverriden ? "blacklisted" : "already exists";
                alt.log(`~ly~[JS] ~lb~Skipping static property ${propKey} in ${cls.name}: ${reason}`);
            }

            continue;
        }

        let descriptor = Object.getOwnPropertyDescriptor(cls, propKey);
        if (descriptor) {
            if (typeof descriptor.get === "function") {
                descriptor = { ...descriptor, get: descriptor.get.bind(cls) };
            }

            Object.defineProperty(baseClass, propKey, descriptor);

            if (options.verbose) {
                alt.log(`~ly~[JS] ~lb~Applied static property ${propKey} in ${cls.name} to ${baseClass.name}`);
            }
        }
    }
}

/**
 * @typedef {Object} Options
 * @property {boolean} verbose - Log verbose informations.
 * @property {Object} blacklist - Properties to exclude from extension.
 * @property {string[]} blacklist.nonStatic
 * @property {string[]} blacklist.static
 * @property {Object} whitelist - Properties allowed to be overwritten. (This will bypass blacklist rules)
 * @property {string[]} whitelist.nonStatic
 * @property {string[]} whitelist.static
 */

/**
 * Extends a base class with properties from other classes.
 *
 * @param {Function} baseClass - The base class to extend.
 * @param {Options | null} options
 * @param {Function[]} classes - Classes whose properties should be added to the base class.
 */
export function extendClassWithProperties(baseClass, options, ...classes) {
    assertIsType(baseClass, "function", `Expected class object, but got ${typeof baseClass}`);

    const _options = {
        ...defaultOptions,
        ...(options || {}),
        blacklist: {
            nonStatic: [...defaultOptions.blacklist.nonStatic, ...(options?.blacklist?.nonStatic || [])],
            static: [...defaultOptions.blacklist.static, ...(options?.blacklist?.static || [])]
        },
        whitelist: {
            nonStatic: [...defaultOptions.whitelist.nonStatic, ...(options?.whitelist?.nonStatic || [])],
            static: [...defaultOptions.whitelist.static, ...(options?.whitelist?.static || [])]
        }
    };

    for (const cls of classes) {
        applyNonStaticProperties(baseClass, cls, _options);
        applyStaticProperties(baseClass, cls, _options);
    }
}

export function overrideLazyProperty(instance, propertyName, value) {
    const descriptor = Object.getOwnPropertyDescriptor(instance, propertyName);

    if (!descriptor) {
        alt.log(`~ly~[JS] ~lr~Lazy Property ${propertyName} does not exist in ${instance.constructor.name} to override property`);
        return;
    }

    const newDescriptor = { ...descriptor };

    if (typeof newDescriptor.get == "function") {
        newDescriptor.get = () => value;
    } else {
        newDescriptor.value = value;
    }

    Object.defineProperty(instance, propertyName, newDescriptor);
}
