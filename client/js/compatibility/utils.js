/// <reference path="../../../types/shared/index.d.ts" />
/// <reference path="../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

/** @type {typeof import("./../../../shared/js/utils.js")} */
const { assert, waitFor, assertRGBA, assertVector2, assertVector3 } = requireBinding("shared/utils.js");

const { SharedUtils } = requireBinding("shared/compatibility/utils.js");

requireBinding("shared/classes/rgba.js");
requireBinding("shared/classes/vector.js");

requireBinding("shared/compatibility/timers.js");

requireBinding("client/events.js");
requireBinding("client/graphics.js");

const natives = cppBindings.getBuiltinModule("@altv/natives");

async function registerPedheadshotBase64(headshotNative, ped) {
    let error = null;
    let headshot = null;

    try {
        headshot = headshotNative(ped);
        assert(natives.isPedheadshotValid(headshot), `Ped or player is invalid: ${ped} (headshot: ${headshot})`);

        await waitFor(() => natives.isPedheadshotReady(headshot));
        return alt.headshotToBase64(headshot);
    } catch (cause) {
        error = new Error(`Failed to get ped headshot base64: ${headshot}`, { cause });
    } finally {
        natives.unregisterPedheadshot(headshot);
    }

    throw error;
}

class Keybind {
    /** @type {Map<number, Keybind[]>} */
    static registeredHandlers = new Map();

    /** @type {number} */
    keyState;

    /** @type {Function} */
    callback;

    // constructor(keyCode: shared.KeyCode | shared.KeyCode[], callback: () => void, eventType?: "keyup" | "keydown");
    constructor(keyCode, callback, eventType) {
        keyCode = Array.isArray(keyCode) ? keyCode : [keyCode];

        assert(
            keyCode.every((code) => typeof code == "number"),
            "Expected a number or array of numbers as first argument"
        );
        assert(typeof callback == "function", "Expected a function as second argument");
        assert(!eventType || eventType == "keyup" || eventType == "keydown", "Expected a string 'keyup' or 'keydown' as third argument");

        this.keyState = eventType == "keyup" ? alt.Enums.KeyState.UP : alt.Enums.KeyState.DOWN;
        this.callback = callback;

        for (const code of keyCode) {
            const boundKeys = Keybind.registeredHandlers.get(code) ?? [];
            boundKeys.push(this);
            Keybind.registeredHandlers.set(code, boundKeys);
        }
    }

    destroy() {
        const boundKeys = (Keybind.registeredHandlers.get(this.keyCode) ?? []).filter((keybind) => keybind != this);

        if (boundKeys.length) Keybind.registeredHandlers.set(this.keyCode, boundKeys);
        else Keybind.registeredHandlers.delete(this.keyCode);
    }
}

const defaultMarkerOptions = {
    type: 0,
    dir: alt.Vector3.zero,
    rot: alt.Vector3.zero,
    scale: alt.Vector3.one,
    color: new alt.RGBA(255, 255, 255),
    bobUpAndDown: false,
    faceCamera: false,
    p19: 2,
    rotate: false,
    textureDict: undefined,
    textureName: undefined,
    drawOnEnts: false
};

class Marker {
    static #markersToRender = new Set();
    static #everyTickTimer = null;

    /** @type {number} */
    #type;
    /** @type {{x: number, y:number, z: number}} */
    #pos;
    /** @type {{x: number, y:number, z: number}} */
    #dir;
    /** @type {{x: number, y:number, z: number}} */
    #rot;
    /** @type {{x: number, y:number, z: number}} */
    #scale;
    /** @type {{r: number, g: number, b: number, a: number | undefined}} */
    #color;
    /** @type {boolean} */
    #bobUpAndDown;
    /** @type {boolean} */
    #faceCamera;
    /** @type {number} */
    #p19;
    /** @type {boolean} */
    #rotate;
    /** @type {string | undefined} */
    #textureDict;
    /** @type {string | undefined} */
    #textureName;
    /** @type {boolean} */
    #drawOnEnts;

    constructor(pos, options = {}) {
        options = { ...defaultMarkerOptions, ...options };

        assertVector3(pos, "Expected Vector3 as first argument");
        assert(typeof options.type === "number", "Expected a number for type option");
        assertVector3(options.dir, "Expected Vector3 for dir option");
        assertVector3(options.rot, "Expected Vector3 for rot option");
        assertVector3(options.scale, "Expected Vector3 for scale option");
        assertRGBA(options.color, "Expected RGBA for color option");
        assert(typeof options.bobUpAndDown === "boolean", "Expected a boolean for bobUpAndDown option");
        assert(typeof options.faceCamera === "boolean", "Expected a boolean for faceCamera option");
        assert(typeof options.p19 === "number", "Expected a number for p19 option");
        assert(typeof options.rotate === "boolean", "Expected a boolean for rotate option");
        assert(typeof options.textureDict === "undefined" || typeof options.textureDict === "string", "Expected a string or undefined for textureDict option");
        assert(typeof options.textureName === "undefined" || typeof options.textureName === "string", "Expected a string or undefined for textureName option");
        assert(typeof options.drawOnEnts === "boolean", "Expected a boolean for drawOnEnts option");

        this.#pos = pos;
        this.#type = options.type;
        this.#dir = options.dir;
        this.#rot = options.rot;
        this.#scale = options.scale;
        this.#color = options.color;
        this.#bobUpAndDown = options.bobUpAndDown;
        this.#faceCamera = options.faceCamera;
        this.#p19 = options.p19;
        this.#rotate = options.rotate;
        this.#textureDict = options.textureDict;
        this.#textureName = options.textureName;
        this.#drawOnEnts = options.drawOnEnts;

        Marker.#markersToRender.add(this);

        if (!Marker.#everyTickTimer) {
            Marker.#everyTickTimer = new alt.Timers.EveryTick(Marker.#render);
        }
    }

    destroy() {
        Marker.#markersToRender.delete(this);

        if (!Marker.#markersToRender.size) {
            Marker.#everyTickTimer.destroy();
            Marker.#everyTickTimer = null;
        }
    }

    static #render() {
        Marker.#markersToRender.forEach((marker) => {
            natives.drawMarker(
                marker.#type,
                marker.#pos.x,
                marker.#pos.y,
                marker.#pos.z,
                marker.#dir.x,
                marker.#dir.y,
                marker.#dir.z,
                marker.#rot.x,
                marker.#rot.y,
                marker.#rot.z,
                marker.#scale.x,
                marker.#scale.y,
                marker.#scale.z,
                marker.#color.r,
                marker.#color.g,
                marker.#color.b,
                marker.#color.a,
                marker.#bobUpAndDown,
                marker.#faceCamera,
                marker.#p19,
                marker.#rotate,
                marker.#textureDict,
                marker.#textureName,
                marker.#drawOnEnts
            );
        });
    }
}

class Utils extends SharedUtils {
    static async requestModel(model, timeout = 5000) {
        assert(typeof model === "string" || typeof model === "number", "Expected a string or number as first argument");
        assert(typeof timeout === "number", "Expected a number as second argument");

        const _model = model;

        if (typeof model === "string") model = alt.hash(model);
        assert(natives.isModelValid(model), typeof _model === "string" ? `Model '${_model}', with hash ${model} is invalid` : `Model ${_model} is invalid`);

        try {
            natives.requestModel(model);
            await waitFor(() => natives.hasModelLoaded(model), timeout);
        } catch (_) {
            throw new Error(`Failed to request model '${_model}'`);
        }
    }

    static async requestAnimDict(animDict, timeout = 5000) {
        assert(typeof animDict === "string", "Expected a string as first argument");
        assert(typeof timeout === "number", "Expected a number as second argument");
        assert(natives.doesAnimDictExist(animDict), `Anim dict '${animDict}' not valid`);

        try {
            natives.requestAnimDict(animDict);
            await waitFor(() => natives.hasAnimDictLoaded(animDict), timeout);
        } catch (_) {
            throw new Error(`Failed to request anim dict '${animDict}'`);
        }
    }

    static async requestAnimSet(animSet, timeout = 5000) {
        assert(typeof animSet === "string", "Expected a string as first argument");
        assert(typeof timeout === "number", "Expected a number as second argument");

        try {
            natives.requestAnimSet(animSet);
            await waitFor(() => natives.hasAnimSetLoaded(animSet), timeout);
        } catch (_) {
            throw new Error(`Failed to request anim (clip) set '${animSet}'`);
        }
    }

    static requestClipSet(...args) {
        return Utils.requestAnimSet(...args);
    }

    static async requestCutscene(cutsceneName, flags, timeout = 5000) {
        assert(typeof cutsceneName === "string", "Expected a string as first argument");
        assert(typeof flags === "number" || typeof flags === "string", "Expected a number or string as second argument");
        assert(typeof timeout === "number", "Expected a number as third argument");

        try {
            natives.requestCutscene(cutsceneName, typeof flags === "string" ? parseInt(flags) : flags);
            await waitFor(() => natives.hasThisCutsceneLoaded(cutsceneName), timeout);
        } catch (_) {
            throw new Error(`Failed to request cutscene '${cutsceneName}'`);
        }
    }

    static async loadMapArea(pos, radius = 50.0, timeout = 5000) {
        assertVector3(pos, "Expected Vector3 as first argument");
        assert(typeof radius === "number", "Expected a number as second argument");
        assert(typeof timeout === "number", "Expected a number as third argument");

        alt.FocusData.focusOverridePos = pos;

        natives.newLoadSceneStop();
        natives.newLoadSceneStartSphere(pos.x, pos.y, pos.z, radius, 0);

        try {
            await waitFor(natives.isNewLoadSceneLoaded, timeout);
        } catch (_) {
            throw new Error(`Failed to load map area pos: { x: ${pos.x.toFixed(2)}, y: ${pos.y.toFixed(2)}, z: ${pos.z.toFixed(2)} }`);
        } finally {
            alt.FocusData.clearFocusOverride();
            natives.newLoadSceneStop();
        }
    }

    static registerPedheadshotBase64(ped) {
        return registerPedheadshotBase64(natives.registerPedheadshot, ped);
    }

    static registerPedheadshot3Base64(ped) {
        return registerPedheadshotBase64(natives.registerPedheadshotHires, ped);
    }

    static registerPedheadshotTransparentBase64(ped) {
        return registerPedheadshotBase64(natives.registerPedheadshotTransparent, ped);
    }

    static getClosestPlayer(options = {}) {
        return alt.Utils.getClosestPlayer(options);
    }

    static getClosestVehicle(options = {}) {
        return alt.Utils.getClosestVehicle(options);
    }

    static getClosestObject(options = {}) {
        return alt.Utils.getClosestObject(options);
    }

    static getClosestWorldObject(options = {}) {
        return alt.Utils.getClosestWorldObject(options);
    }

    static getClosestVirtualEntity(options = {}) {
        return alt.Utils.getClosestVirtualEntity(options);
    }

    static Keybind = Keybind;
    static Marker = Marker;

    static drawText2dThisFrame = alt.Drawing.drawText2dThisFrame;
    static drawText2d = alt.Drawing.drawText2d;
    static drawText3dThisFrame = alt.Drawing.drawText3dThisFrame;
    static drawText3d = alt.Drawing.drawText3d;
}

cppBindings.registerCompatibilityExport("Utils", Utils);

alt.Events.onKeyBoardEvent(({ key, state }) => {
    if (!Keybind.registeredHandlers.has(key)) return;

    const boundKeys = Keybind.registeredHandlers.get(key);
    const filteredKeys = boundKeys.filter((keybind) => keybind.keyState === state) ?? [];

    for (const keybind of filteredKeys) {
        keybind.callback?.();
    }
});
