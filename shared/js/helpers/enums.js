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
