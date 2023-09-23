// Class helper functions

/**
 * @param {unknown} class_
 * @param {string} prop
 * @param {() => any} getter
 * @param {(value: any) => void} setter
 */
export function addGetterSetter(class_, prop, getter, setter) {
    if (!class_) return;

    Object.defineProperty(class_.prototype, prop, {
        get: getter,
        set: setter
    });
}
