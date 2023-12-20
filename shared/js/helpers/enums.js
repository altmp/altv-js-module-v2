/**
 *
 * @param {string[]} values
 */
export function createNumericEnum(values) {
    const temp = {};
    for (let i = 0; i < values.length; ++i) {
        temp[values[i]] = i;
    }

    return Object.freeze(temp);
}

/**
 *
 * @param {Object} obj
 */
export function createReverseLookupObject(obj) {
    const newObj = {};

    for (const key in obj) {
        newObj[obj[key]] = key;
        newObj[key] = obj[key];
    }

    return Object.freeze(newObj);
}
