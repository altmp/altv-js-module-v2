/// <reference types="../shared/index.d.ts" />

/**
 * @module @altv/client
 */

declare module "@altv/client" {
    import altShared from "@altv/shared";

    export const isStreamerModeEnabled: boolean;
    export const locale: altShared.Enums.Locale;
    export const licenseHash: string;
    export const clientConfig: Readonly<Record<string, unknown>>;
    export const clientPath: string;

    export function isMenuOpen(): boolean;
    export function isConsoleOpen(): boolean;
    export function isGameFocused(): boolean;
    export function getFps(): number;
    export function getPing(): number;
    export function getTotalPacketsSent(): number;
    export function getTotalPacketsLost(): number;
    export function getServerIp(): string;
    export function getServerPort(): number;
    export function getScreenResolution(): altShared.Vector2;
    export function isFullscreen(): boolean;
    export function areGameControlsActive(): boolean;
    export function setGameControlsActive(): boolean;
    export function getMsPerGameMinute(): number;
    export function setMsPerGameMinute(ms: number): void;
    export function areRmlControlsActive(): boolean;
    export function setRmlControlsActive(state: boolean): void;
    export function getKeyState(key: altShared.Enums.KeyCode): altShared.KeyStateInfo;
    export function beginScaleformMovieMethodMinimap(methodName: string): void;
    export function setWeatherCycle(weathers: altShared.WeatherCycle[]): void;
    export function setWeatherSyncActive(state: boolean): void;
    export function getPermissionState(permission: altShared.Enums.Permission): boolean;
    export function takeScreenshot(gameOnly?: boolean): Promise<string>;
    export function setAngularVelocity(entity: altShared.Entity, quaternion: altShared.Quaternion): void;
    export function headshotToBase64(id: number): string;
    export function setDlcClothes(scriptId: number, component: number, drawable: number, texture: number, palette?: number, dlc?: number): void;
    export function setDlcProps(scriptId: number, component: number, drawable: number, texture: number, dlc?: number): void;
    export function clearProps(scriptId: number, component: number): void;
    export function setWatermarkPosition(position: Enums.WatermarkPosition): void;
    export function copyToClipboard(str: string): void;
    export function toggleRmlDebugger(state: boolean): void;
    export function loadRmlFontFace(path: string, name: string, isItalic?: boolean, isBold?: boolean): void;
    export function worldToScreen(pos: altShared.Vector3): altShared.Vector3;
    export function screenToWorld(pos: altShared.Vector2): altShared.Vector3;
    export function setMinimapComponentPosition(name: string, alignX: string, alignY: string, pos: altShared.Vector2, size: altShared.Vector2): void;
    export function resetMinimapComponentPosition(name: string): void;
    export function setMinimapIsRectangle(state: boolean): void;
    export function getPedBonePos(scriptId: number, boneId: number): altShared.Vector3;

    export abstract class AudioCategory {
        readonly name: string;
        volume: number;
        distanceRolloffScale: number;
        plateauRolloffScale: number;
        occlusionDamping: number;
        environmentalFilterDamping: number;
        sourceReverbDamping: number;
        distanceReverbDamping: number;
        interiorReverbDamping: number;
        environmentalLoudness: number;
        underwaterWetLevel: number;
        stonedWetLevel: number;
        pitch: number;
        lowPassFilterCutoff: number;
        highPassFilterCutoff: number;

        reset(): void;

        static get(name: string): AudioCategory | undefined;
    }

    export abstract class AudioFilter {
        audioCategory: AudioCategory;
        readonly hash: number;

        addRotateEffect(rate: number, priority: number): number;
        addVolumeEffect(volume: number, priority: number): number;
        addPeakeqEffect(band: number, bandwidth: number, q: number, center: number, gain: number, priority: number): number;
        addDampEffect(target: number, quiet: number, rate: number, gain: number, delay: number, priority: number): number;
        addAutowahEffect(dryMix: number, wetMix: number, feedback: number, rate: number, range: number, freq: number, priority: number): number;
        addPhaserEffect(dryMix: number, wetMix: number, feedback: number, rate: number, range: number, freq: number, priority: number): number;
        addChorusEffect(dryMix: number, wetMix: number, feedback: number, minSweep: number, maxSweep: number, rate: number, priority: number): number;
        addDistortionEffect(drive: number, dryMix: number, wetMix: number, feedback: number, volume: number, priority: number): number;
        addCompressor2Effect(gain: number, threshold: number, ratio: number, attack: number, release: number, priority: number): number;
        addBqfEffect(filter: number, center: number, gain: number, bandwidth: number, q: number, s: number, priority: number): number;
        addEcho4Effect(dryMix: number, wetMix: number, feedback: number, delay: number, priority: number): number;
        addPitchshiftEffect(pitchShift: number, semitones: number, fftSize: number, osamp: number, priority: number): number;
        addFreeverbEffect(dryMix: number, wetMix: number, roomSize: number, damp: number, width: number, mode: number, priority: number): number;

        removeEffect(fxHandler: number): boolean;
    }

    export abstract class AudioOutput extends altShared.BaseObject {
        muted: boolean;
        volume: number;
        readonly category: number;
        readonly owner: altShared.BaseObject;

        filter: AudioFilter | null;
    }

    export abstract class AudioOutputAttached extends AudioOutput {
        entity: altShared.WorldObject;
    }

    export abstract class AudioOutputFrontend extends AudioOutput {}

    export abstract class AudioOutputWorld extends AudioOutput {
        pos: altShared.Vector3;
    }

    export abstract class Blip extends altShared.Blip {
        readonly scriptID: number;
        readonly isStreamedIn: boolean;
    }

    export abstract class Checkpoint extends altShared.Checkpoint {
        readonly scriptID: number;
        readonly isStreamedIn: boolean;
    }

    export abstract class ColShape extends WorldObject {
        readonly colShapeType: altShared.Enums.ColShapeType;
        playersOnly: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(pos: altShared.Vector3): boolean;
    }

    export abstract class Entity extends altShared.Entity {
        readonly scriptID: number;
    }

    export abstract class Font extends altShared.BaseObject {
        static register(path: string): Font | undefined;
    }

    export abstract class Handling extends HandlingData {
        readonly isModified: boolean;

        reset(): void;
    }

    export abstract class HandlingData {
        readonly handlingNameHash: number;

        mass: number;
        initialDragCoeff: number;
        downforceModifier: number;
        unkFloat1: number;
        unkFloat2: number;
        unkFloat4: number;
        unkFloat5: number;
        centreOfMassOffset: number;
        inertiaMultiplier: number;
        percentSubmerged: number;
        percentSubmergedRatio: number;
        driveBiasFront: number;
        acceleration: number;
        initialDriveGears: number;
        driveInertia: number;
        clutchChangeRateScaleUpShift: number;
        clutchChangeRateScaleDownShift: number;
        initialDriveForce: number;
        driveMaxFlatVel: number;
        initialDriveMaxFlatVel: number;
        brakeForce: number;
        brakeBiasFront: number;
        brakeBiasRear: number;
        handBrakeForce: number;
        steeringLock: number;
        steeringLockRatio: number;
        tractionCurveMax: number;
        tractionCurveMaxRatio: number;
        tractionCurveMin: number;
        tractionCurveMinRatio: number;
        tractionCurveLateral: number;
        tractionCurveLateralRatio: number;
        tractionSpringDeltaMax: number;
        tractionSpringDeltaMaxRatio: number;
        lowSpeedTractionLossMult: number;
        camberStiffness: number;
        tractionBiasFront: number;
        tractionBiasRear: number;
        tractionLossMult: number;
        suspensionForce: number;
        suspensionCompDamp: number;
        suspensionReboundDamp: number;
        suspensionUpperLimit: number;
        suspensionLowerLimit: number;
        suspensionRaise: number;
        suspensionBiasFront: number;
        suspensionBiasRear: number;
        antiRollBarForce: number;
        antiRollBarBiasFront: number;
        antiRollBarBiasRear: number;
        rollCentreHeightFront: number;
        rollCentreHeightRear: number;
        collisionDamageMult: number;
        weaponDamageMult: number;
        deformationDamageMult: number;
        engineDamageMult: number;
        petrolTankVolume: number;
        oilVolume: number;
        seatOffsetDistX: number;
        seatOffsetDistY: number;
        seatOffsetDistZ: number;
        monetaryValue: number;
        modelFlags: number;
        handlingFlags: number;
        damageFlags: number;

        static get(modelHash: number | string): HandlingData | undefined;
    }

    export type HttpResponse = { statusCode: number; headers: Readonly<Record<string, string>>; body: string };

    export abstract class HttpClient {
        get(url: string): Promise<HttpResponse>;
        head(url: string): Promise<HttpResponse>;
        post(url: string, body: string): Promise<HttpResponse>;
        put(url: string, body: string): Promise<HttpResponse>;
        delete(url: string, body: string): Promise<HttpResponse>;
        connect(url: string, body: string): Promise<HttpResponse>;
        options(url: string, body: string): Promise<HttpResponse>;
        trace(url: string, body: string): Promise<HttpResponse>;
        patch(url: string, body: string): Promise<HttpResponse>;

        readonly extraHeaders: Record<string, string>;
    }

    export abstract class LocalObject extends altShared.Object {
        get model(): number;
        set model(value: number | string);
        alpha: number;
        readonly isDynamic: boolean;
        lodDistance: number;
        hasGravity: number;
        readonly isCollisionEnabled: boolean;
        positionFrozen: boolean;
        textureVariation: number;
        readonly isWorldObject: boolean;
        readonly isWeaponObject: boolean;
        readonly useStreaming: boolean;
        readonly streamingDistance: number;
        visible: boolean;

        resetAlpha(): void;
        attachTo(target: number | Entity, boneIndex: number, pos: altShared.Vector3, rot: altShared.Vector3, useSoftPinning: boolean, collision: boolean, fixedRot: boolean): void;
        detach(dynamic: boolean): void;
        toggleCollision(toggle: boolean, keepPhysics: boolean): void;
        placeOnGroundProperly(): void;
        activatePhysics(): void;

        static readonly allWorld: ReadonlyArray<LocalObject>;
    }

    export abstract class LocalPed extends altShared.Ped {
        get model(): number;
        set model(value: number | string);
        readonly streamingDistance: number;
        visible: boolean;
        readonly scriptID: number;
        readonly isStreamedIn: boolean;
    }

    export abstract class LocalPlayer extends Player {
        readonly currentAmmo: number;
        stamina: number;
        maxStamina: number;
        readonly currentWeaponData: WeaponData;
        readonly weapons: ReadonlyArray<{ hash: number; tintIndex: number; components: ReadonlyArray<number> }>;

        getWeaponAmmo(wepaonHash: number | string): number | undefined;
        hasWeapon(wepaonHash: number | string): boolean;
        getWeaponComponents(wepaonHash: number | string): ReadonlyArray<number> | undefined;
    }

    export abstract class LocalVehicle extends Vehicle {
        get model(): number;
        set model(value: number | string);

        readonly streamingDistance: number;
        visible: boolean;
        readonly scriptID: number;
        readonly isStreamedIn: boolean;
    }

    export abstract class MapZoomData {
        fZoomScale: number;
        fZoomSpeed: number;
        fScrollSpeed: number;
        vTilesX: number;
        vTilesY: number;

        reset(): void;

        static get(idOrAlias: number | string): MapZoomData | undefined;
        static resetAll(): void;
    }

    export abstract class Player extends altShared.Player {
        readonly isTalking: boolean;
        readonly micLevel: number;
        spatialVolume: number;
        nonSpatialVolume: number;
        readonly filter: AudioFilter;

        static readonly local: LocalPlayer;
    }

    export abstract class RmlDocument extends RmlElement {
        title: string;
        readonly sourceUrl: string;
        readonly isVisible: boolean;
        readonly isModal: boolean;

        readonly body: RmlElement;

        show(isModal?: boolean, focused?: boolean): void;
        hide(): void;
        update(): void;

        createElement(tag: string): RmlElement | undefined;
        createTextNode(text: string): RmlElement | undefined;
    }

    export abstract class RmlElement extends altShared.BaseObject {
        readonly relativeOffset: altShared.Vector2;
        readonly absoluteOffset: altShared.Vector2;
        readonly baseline: number;
        readonly zIndex: number;
        readonly containingBlock: altShared.Vector2;

        readonly focusedElement?: RmlElement;
        readonly tagName: string;
        rmlID: string;
        readonly isOwned: boolean;
        readonly absoluteLeft: number;
        readonly absoluteTop: number;
        readonly clientLeft: number;
        readonly clientTop: number;
        readonly clientWidth: number;
        readonly clientHeight: number;
        readonly offsetLeft: number;
        readonly offsetTop: number;
        readonly offsetWidth: number;
        readonly offsetHeight: number;
        scrollLeft: number;
        scrollTop: number;
        readonly scrollWidth: number;
        readonly scrollHeight: number;
        readonly isVisible: boolean;

        readonly parent?: RmlElement;
        readonly nextSibling?: RmlElement;
        readonly previousSibling?: RmlElement;
        readonly firstChild?: RmlElement;
        readonly lastChild?: RmlElement;
        readonly childCount: number;
        readonly hasChildren: boolean;
        innerRML: string;
        readonly childNodes: ReadonlyArray<RmlElement>;

        readonly ownerDocument: RmlDocument;
        readonly attributes: Readonly<Record<string, string>>;
        readonly classList: ReadonlyArray<string>;
        readonly pseudoClassList: ReadonlyArray<string>;

        readonly style: Record<string, string>;

        addClass(name: string): boolean;
        removeClass(name: string): boolean;
        hasClass(name: string): boolean;
        addPseudoClass(name: string): boolean;
        removePseudoClass(name: string): boolean;
        hasPseudoClass(name: string): boolean;
        setOffset(offsetParent: RmlElement, offset: altShared.Vector2, fixed?: boolean): void;
        isPointWithinElement(point: altShared.Vector2): boolean;
        setProperty(name: string, value: string): boolean;
        removeProperty(name: string): boolean;
        hasProperty(name: string): boolean;
        hasLocalProperty(name: string): boolean;
        getProperty(name: string): string;
        getLocalProperty(name: string): string;
        getPropertyAbsoluteValue(): number;
        setAttribute(name: string, value: string): void;
        removeAttribute(name: string): boolean;
        hasAttribute(name: string): boolean;
        getAttribute(name: string): string;
        getClosest(selectors: string): RmlElement | null;
        getChild(index: number): RmlElement | null;
        appendChild(child: RmlElement): void;
        insertBefore(element: RmlElement, adjacentElement: RmlElement): void;
        replaceChild(element: RmlElement, oldElement: RmlElement): void;
        removeChild(child: RmlElement): void;

        focus(): boolean;
        blur(): void;
        click(): void;

        scrollIntoView(alignWithTop?: boolean): void;
        getElementByID(id: string): RmlElement | null;
        getElementsByTagName(tag: string): ReadonlyArray<RmlElement>;
        getElementsByClassName(tag: string): ReadonlyArray<RmlElement>;
        querySelector(selector: string): RmlElement | null;
        querySelectorAll(selector: string): ReadonlyArray<RmlElement>;
    }

    export abstract class TextLabel extends WorldObject {
        readonly isStreamedIn: boolean;
        readonly isGlobal: boolean;
        readonly target: Entity;
        visible: boolean;
        color: altShared.RGBA;
        scale: altShared.Vector2;
        rot: number;
        faceCamera: boolean;
        readonly streamingDistance: number;
    }

    export abstract class Vehicle extends altShared.Vehicle {
        readonly speed: number;
        readonly gear: number;
        readonly maxGear: number;
        readonly rpm: number;
        readonly wheelsCount: number;
        readonly speedVector: altShared.Vector3;
        readonly handling: Handling;
        readonly isHandlingModified: boolean;
        indicatorLights: number;
        seatCount: number;
        readonly occupiedSeatsCount: number;
        readonly isTaxiLightOn: boolean;
        engineTemperature: number;
        fuelLevel: number;
        oilLevel: number;
        engineLightState: boolean;
        absLightState: boolean;
        petrolLightState: boolean;
        oilLightState: boolean;
        batteryLightState: boolean;
        suspensionHeight: number;

        resetHandling(): void;
        replaceHandling(): void;
        toggleTaxiLight(state: boolean): void;
        getWheelCamber(wheelId: number): number;
        setWheelCamber(wheelId: number, value: number): void;
        getWheelTrackWidth(wheelId: number): number;
        setWheelTrackWidth(wheelId: number, value: number): void;
        getWheelHeight(wheelId: number): number;
        setWheelHeight(wheelId: number, value: number): void;
        getWheelTyreRadius(wheelId: number): number;
        setWheelTyreRadius(wheelId: number, radius: number): void;
        getWheelRimRadius(wheelId: number): number;
        setWheelRimRadius(wheelId: number, radius: number): void;
        getWheelTyreWidth(wheelId: number): number;
        setWheelTyreWidth(wheelId: number, width: number): void;
        getWheelSurfaceMaterial(wheelId: number): number;
        resetDashboardLights(): void;
    }

    export abstract class VirtualEntity extends altShared.VirtualEntity {
        readonly isStreamedIn: boolean;
    }

    export abstract class WeaponData {
        readonly modelHash: number;
        readonly nameHash: number;

        recoilShakeAmplitude: number;
        recoilAccuracyMax: number;
        recoilAccuracyToAllowHeadshotPlayer: number;
        recoilRecoveryRate: number;
        animReloadRate: number;
        vehicleReloadTime: number;
        lockOnRange: number;
        accuracySpread: number;
        range: number;
        damage: number;
        readonly clipSize: number;
        readonly timeBetweenShots: number;
        headshotDamageModifier: number;
        playerDamageModifier: number;

        static get(weaponHash: number | string): WeaponData | undefined;
    }

    export abstract class WebSocketClient extends altShared.BaseObject {
        url: string;
        autoReconnect: boolean;
        perMessageDeflate: boolean;
        pingInterval: number;
        readonly readyState: boolean;

        start(): void;
        stop(): void;

        send(message: string | altShared.Buffer): boolean;

        addSubProtocol(protocol: string): void;
        getSubProtocols(): ReadonlyArray<string>;
        setExtraHeader(name: string, value: string): void;
        getExtraHeaders(): Readonly<Record<string, string>>;
    }

    export abstract class WebView extends altShared.BaseObject {
        focused: boolean;
        url: string;
        visible: boolean;

        readonly isOverlay: boolean;
        readonly isLoaded: boolean;
        readonly isReady: boolean;

        size: altShared.Vector2;
        position: altShared.Vector3;

        readonly outputs: ReadonlyArray<AudioOutput>;

        emit(eventName: string, ...args: unknown[]): void;
        setExtraHeader(name: string, value: string): void;
        setZoomLevel(value: number): void;
        reload(ignoreCache: boolean): void;

        addOutput(output: AudioOutput): void;
        removeOutput(output: AudioOutput): void;

        static readonly isGpuAccelerationActive: boolean;
    }

    export abstract class WorldObject extends altShared.WorldObject {
        dimension: number;
        pos: altShared.Vector3;
    }

    export namespace Enum {
        export const enum WatermarkPosition {
            BottomRight = 0,
            TopRight = 1,
            TopLeft = 2,
            TopCenter = 3,
            BottomCenter = 4
        }

        // TODO (xLuxy): Maybe shared?
        export const enum StatName {
            Stamina = "stamina",
            Strength = "strength",
            LungCapacity = "lung_capacity",
            Wheelie = "wheelie_ability",
            Flying = "flying_ability",
            Shooting = "shooting_ability",
            Stealth = "stealth_ability"
        }

        // TODO (xLuxy): Maybe shared?
        export const enum ConfigFlag {
            DisableAutoWeaponSwap = "DISABLE_AUTO_WEAPON_SWAP",
            DisablePedPropKnockOff = "DISABLE_PED_PROP_KNOCK_OFF",
            DisableIdleCamera = "DISABLE_IDLE_CAMERA",
            DisableVehicleEngineShutdownOnLeave = "DISABLE_VEHICLE_ENGINE_SHUTDOWN_ON_LEAVE",
            /** @beta */
            DisableSPEnterVehicleClipset = "DISABLE_SP_ENTER_VEHICLE_CLIPSET",
            /** @beta */
            ForceRenderSnow = "FORCE_RENDER_SNOW",
            /** @beta */
            ForceHideNightProps = "FORCE_HIDE_NIGHT_PROPS",
            /** @beta */
            ForceShowNightProps = "FORCE_SHOW_NIGHT_PROPS",
            /** @beta */
            DisableEmissiveLightsRendering = "DISABLE_EMISSIVE_LIGHTS_RENDERING"
        }
    }

    export namespace Events {
        export let rawEmitEnabled: boolean;
        export function emit(eventName: string, ...args: unknown[]): void;

        export function emitServer(eventName: string, ...args: unknown[]): void;
        export function emitServerUnreliable(eventName: string, ...args: unknown[]): void;
    }

    export namespace Discord {
        export const isReady: boolean;
        export const userID: number;
        export const userName: string;
        export const discriminator: string;
        export const avatar: string;

        export function requestOAuth2Token(appId: string): Promise<string>;
    }

    export namespace Voice {
        export let inputMuted: boolean;
        export let activityInputEnabled: boolean;
        export let activationLevel: number;
        export const activationKey: altShared.Enums.KeyCode;
        export const voiceControlsEnabled: boolean;
        export let noiseSuppressionEnabled: boolean;
        export let inputDevice: string | null;

        export const availableInputDevices: ReadonlyArray<{
            uid: string;
            name: string;
        }>;

        export function toggleInput(enabled: boolean): void;
    }

    export namespace LocalStorage {
        export function get(key: string): unknown;
        export function set(key: string, value: unknown): void;
        export function has(key: string): boolean;
        export function remove(key: string): void;
        export function clear(): void;
        export function save(): void;
    }

    export namespace Stats {
        export function set(statName: Enums.StatName, value: number | boolean | string): void;
        export function get(statName: Enums.StatName): number | boolean | string | undefined;
        export function reset(statName: Enums.StatName): void;
    }

    export namespace FocusData {
        export const isFocusOverriden: boolean;
        export let focusOverridePos: altShared.Vector3;
        export let focusOverrideEntity: Entity | null;

        export function clearFocusOverride(): void;
    }

    export namespace Gxt {
        export function add(nameOrHash: number | string): void;
        export function remove(nameOrHash: number | string): void;
        export function get(nameOrHash: number | string): string;
    }

    export namespace Cursor {
        export let visible: boolean;
        export let pos: altShared.Vector2;
        export let posNormalized: altShared.Vector2;
    }

    export namespace Cam {
        export const pos: altShared.Vector3;
        export let frozen: boolean;
    }

    export namespace Streaming {
        export function doesTextureExistInArchetype(modelNameOrHash: number | string, textureName: string): boolean;
        export function requestIpl(iplName: string): void;
        export function removeIpl(iplName: string): void;
        export function loadDefaultIpls(): void;
        export function loadModel(modelNameOrHash: number | string, isAsync?: boolean): void;
        export function loadYtyp(ytyp: string): void;
        export function unloadYtyp(ytyp: string): void;
    }

    export namespace ConfigFlag {
        export function get(flag: Enums.ConfigFlag): boolean;
        export function set(flag: Enums.ConfigFlag, state: boolean): boolean;
        export function exists(flag: Enums.ConfigFlag): boolean;
    }

    export * from "@altv/shared";
}
