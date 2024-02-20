/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/server/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/**
 *
 * @param {string} key
 */
function deleteMeta(key) {
    delete alt.meta[key];
}

/**
 *
 * @param {string} key
 * @returns unknown
 */
function getMeta(key) {
    return alt.meta[key];
}

/**
 *
 * @returns string[]
 */
function getMetaKeys() {
    const keys = Object.keys(alt.meta);
    return Object.freeze(keys);
}

/**
 *
 * @param {string} key
 * @returns boolean
 */
function hasMeta(key) {
    return !!alt.meta[key];
}

/**
 *
 * @param {string} key
 * @param {unknown} value
 */
function setMeta(key, value) {
    alt.meta[key] = value;
}

/**
 *
 * @param {string} key
 * @returns unknown
 */
function getSyncedMeta(key) {
    return alt.syncedMeta[key];
}

/**
 *
 * @returns string[]
 */
function getSyncedMetaKeys() {
    const keys = Object.keys(alt.syncedMeta);
    return Object.freeze(keys);
}

/**
 *
 * @param {string} key
 * @returns boolean
 */
function hasSyncedMeta(key) {
    return alt.syncedMeta[key] === undefined;
}

cppBindings.registerCompatibilityExport("deleteMeta", deleteMeta);
cppBindings.registerCompatibilityExport("getMeta", getMeta);
cppBindings.registerCompatibilityExport("getMetaKeys", getMetaKeys);
cppBindings.registerCompatibilityExport("hasMeta", hasMeta);
cppBindings.registerCompatibilityExport("setMeta", setMeta);
cppBindings.registerCompatibilityExport("getSyncedMeta", getSyncedMeta);
cppBindings.registerCompatibilityExport("getSyncedMetaKeys", getSyncedMetaKeys);
cppBindings.registerCompatibilityExport("hasSyncedMeta", getSyncedMetaKeys);
