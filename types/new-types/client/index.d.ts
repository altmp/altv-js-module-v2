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
    export function setWatermarkPosition(position: altShared.Enums.WatermarkPosition): void;
    export function copyToClipboard(str: string): void;
    export function toggleRmlDebugger(state: boolean): void;
    export function loadRmlFontFace(path: string, name: string, isItalic?: boolean, isBold?: boolean): void;
    export function worldToScreen(pos: altShared.Vector3): altShared.Vector3;
    export function screenToWorld(pos: altShared.Vector2): altShared.Vector3;
    export function setMinimapComponentPosition(name: string, alignX: string, alignY: string, pos: altShared.Vector2, size: altShared.Vector2): void;
    export function resetMinimapComponentPosition(name: string): void;
    export function setMinimapIsRectangle(state: boolean): void;
    export function getPedBonePos(scriptId: number, boneId: number): altShared.Vector3;

    interface AudioCreateOptions {
        source: string;
        volume: number;
        isRadio?: boolean; // default: false
    }

    export abstract class Audio {
        source: string;
        loop: boolean;
        volume: number;

        readonly outputs: ReadonlyArray<AudioOutput>;
        readonly currentTime: number;
        readonly maxTime: number;
        readonly isPlaying: boolean;

        addOutput(output: AudioOutput): void;
        removeOutput(output: AudioOutput): void;
        play(): void;
        pause(): void;
        reset(): void;
        seek(time: number): void;

        static create(options: AudioCreateOptions): Audio | null;
        static getByID(id: number): Audio | null;
    }

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

    interface AudioFilterCreateOptions {
        hash: number | string;
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

        static create(options: AudioFilterCreateOptions): AudioFilter | null;
        static getByID(id: number): AudioFilter | null;
    }

    export abstract class AudioOutput extends altShared.BaseObject {
        muted: boolean;
        volume: number;
        readonly category: number;
        readonly owner: altShared.BaseObject;

        filter: AudioFilter | null;

        static getByID(id: number): AudioOutput | null;
    }

    interface AudioOutputAttachedCreateOptions {
        entity: WorldObject;
        categoryHash?: number; // default: 'radio' hashed
    }

    export abstract class AudioOutputAttached extends AudioOutput {
        entity: altShared.WorldObject;

        static create(options: AudioOutputAttachedCreateOptions): AudioOutputAttached | null;
    }

    interface AudioOutputFrontendCreateOptions {
        //
        categoryHash?: number; // default: 'radio' hashed
    }

    export abstract class AudioOutputFrontend extends AudioOutput {
        static create(options: AudioOutputFrontendCreateOptions): AudioOutputFrontendCreateOptions | null;
    }

    interface AudioOutputWorldCreateOptions {
        pos: altShared.Vector3;
        categoryHash?: number; // default: 'radio' hashed
    }

    export abstract class AudioOutputWorld extends AudioOutput {
        pos: altShared.Vector3;

        static create(options: AudioOutputWorldCreateOptions): AudioOutputWorld | null;
    }

    type BlipCreateOptions = ({ blipType: altShared.Enums.BlipType.AREA } & altShared.AreaBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.RADIUS } & altShared.RadiusBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.DESTINATION } & altShared.PointBlipCreateOptions);

    export abstract class Blip extends altShared.Blip {
        readonly scriptID: number;
        readonly isStreamedIn: boolean;

        static create(options: BlipCreateOptions): Blip | null;
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

        static getByID(id: number): HttpClient | null;
    }

    interface LocalObjectCreateOptions {
        model: number | string;
        pos: altShared.Vector3;
        rot: altShared.Vector3;
        noOffset?: boolean; // default: false
        dynamic?: boolean; // default: false
        useStreaming?: boolean; // default: false
        streamingDistance?: number; // default: 0
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

        static create(options: LocalObjectCreateOptions): LocalObject | null;
        static getByID(id: number): LocalObject | null;
    }

    interface WeaponObjectCreateOptions {
        pos: altShared.Vector3;
        rot: altShared.Vector3;
        weapon: number | string;
        model: number | string;
        ammoCount?: number; // default: 100
        createDefaultComponents?: boolean; // default: true
        scale?: number; // default: 1
        useStreaming?: boolean; // default: false
        streamingDistance?: number; // default: 0
    }

    export namespace WeaponObject {
        export function create(options: WeaponObjectCreateOptions): LocalObject | null;
    }

    interface LocalPedCreateOptions {
        model: number | string;
        dimension: number;
        pos: altShared.Vector3;
        heading?: number; // default: 0
        useStreaming?: boolean; // default: true
        streamingDistance?: number; // default: 0
    }

    export abstract class LocalPed extends altShared.Ped {
        get model(): number;
        set model(value: number | string);
        readonly streamingDistance: number;
        visible: boolean;
        readonly scriptID: number;
        readonly isStreamedIn: boolean;

        static create(options: LocalPedCreateOptions): LocalPed | null;
        static getByID(id: number): LocalPed | null;
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

    interface LocalVehicleCreateOptions {
        model: number | string;
        dimension: number;
        pos: altShared.Vector3;
        rot: altShared.Vector3;
        useStreaming?: boolean; // default: true
        streamingDistance?: number; // default: 300
    }

    export abstract class LocalVehicle extends Vehicle {
        get model(): number;
        set model(value: number | string);

        readonly streamingDistance: number;
        visible: boolean;
        readonly scriptID: number;
        readonly isStreamedIn: boolean;

        static create(opts: LocalVehicleCreateOptions): LocalVehicle | null;
        static getByID(id: number): LocalVehicle | null;
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

    interface RmlDocumentCreateOptions {
        url: string;
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

        static create(options: RmlDocumentCreateOptions): RmlDocument | null;

        // TODO (xLuxy): Check if RmlDocument has (it's not undefined)
        static getByID(id: string): RmlDocument | null;
    }

    // @ts-ignore - Suppresses "Class static side incorrectly extends base class static side"
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

        // TODO (xLuxy): Check if RmlElement has (it's not undefined)
        static getByID(id: string): RmlElement | null;
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

        static getByID(id: number): TextLabel | null;
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

    interface WebSocketClientCreateOptions {
        url: string;
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

        static create(options: WebSocketClientCreateOptions): WebSocketClient | null;
        static getByID(id: number): WebSocketClient | null;
    }

    interface _WebViewTextureCreateOptions {
        drawable: number | string; // default: 0
        targetTexture: string;
    }

    interface _WebViewCreateOptions {
        pos?: altShared.Vector2; // default: { x: 0, y: 0 }
        size?: altShared.Vector2; // default: { x: 0, y: 0 }
        isVisible?: boolean; // default: true
        isOverlay?: boolean; // default: false
    }

    type WebViewCreateOptions = { url: string } & (({ drawable: number | string } & _WebViewTextureCreateOptions) | ({ drawable: never } & _WebViewCreateOptions));

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

        static create(options: WebViewCreateOptions): WebView | null;
    }

    export abstract class WorldObject extends altShared.WorldObject {
        dimension: number;
        pos: altShared.Vector3;
    }

    export namespace PointBlip {
        export function create(opts: altShared.PointBlipCreateOptions): Blip | null;
    }

    export namespace AreaBlip {
        export function create(opts: altShared.AreaBlipCreateOptions): Blip | null;
    }

    export namespace RadiusBlip {
        export function create(opts: altShared.RadiusBlipCreateOptions): Blip | null;
    }

    export namespace Events {
        export let rawEmitEnabled: boolean;
        export function emit(eventName: string, ...args: unknown[]): void;

        export function emitServer(eventName: string, ...args: unknown[]): void;
        export function emitServerUnreliable(eventName: string, ...args: unknown[]): void;

        export function onKeyBoardEvent(callback: GenericEventCallback<KeyBoardEventParameters>): void;
        export function onKeyUp(callback: GenericEventCallback<KeyUpDownEventParameters>): void;
        export function onKeyDown(callback: GenericEventCallback<KeyUpDownEventParameters>): void;
        export function onWebViewEvent(callback: GenericEventCallback<WebViewEventParameters>): void;
        export function onWebSocketEvent(callback: GenericEventCallback<WebSocketEventParameters>): void;
        export function onAudioEvent(callback: GenericEventCallback<AudioEventParameters>): void;
        export function onRmluiEvent(callback: GenericEventCallback<RmluiEventParameters>): void;
        export function onWindowFocusChange(callback: GenericEventCallback<WindowFocusChangeEventParameters>): void;
        export function onWindowResolutionChange(callback: GenericEventCallback<WindowResolutionChangeEventParameters>): void;
        export function onConnectionComplete(callback: GenericEventCallback): void;
        export function onDisconnect(callback: GenericEventCallback): void;
        export function onSpawned(callback: GenericEventCallback): void;

        export function onGameEntityCreate(callback: GenericEventCallback<GameEntityCreateEventParameters>): void;
        export function onGameEntityDestroy(callback: GenericEventCallback<GameEntityDestroyEventParameters>): void;
        export function onEntityHitEntity(callback: GenericEventCallback<EntityHitEntityEventParameters>): void;
        export function onTaskChange(callback: GenericEventCallback<TaskChangeEventParameters>): void;

        export function onPlayerWeaponShoot(callback: GenericEventCallback<PlayerWeaponShootEventParameters>): void;
        export function onPlayerBulletHit(callback: GenericEventCallback<PlayerBulletHitEventParameters>): void;
        export function onPlayerWeaponChange(callback: GenericEventCallback<PlayerWeaponChangeEventParameters>): void;
        export function onPlayerStartEnterVehicle(callback: GenericPlayerEventCallback<PlayerStartEnterVehicleEventParameters>): void;
        export function onPlayerStartLeaveVehicle(callback: GenericPlayerEventCallback<PlayerStartLeaveVehicleEventParameters>): void;
        export function onVoiceConnectionUpdate(callback: GenericEventCallback<VoiceConnectionEventParameters>): void;

        export function onWorldObjectPositionChange(callback: GenericEventCallback<WorldObjectPositionChangeEventParameters>): void;
        export function onWorldObjectStreamIn(callback: GenericEventCallback<WorldObjectStreamInEventParameters>): void;
        export function onWorldObjectStreamOut(callback: GenericEventCallback<WorldObjectStreamOutEventParameters>): void;

        interface WorldObjectPositionChangeEventParameters {
            object: WorldObject;
            oldPos: altShared.Vector3;
        }

        interface WorldObjectStreamInEventParameters {
            object: WorldObject;
        }

        interface WorldObjectStreamOutEventParameters {
            object: WorldObject;
        }

        interface VoiceConnectionEventParameters {
            state: altShared.Enums.VoiceConnectionState;
        }

        interface PlayerWeaponShootEventParameters {
            weapon: number;
            totalAmmo: number;
            ammoInClip: number;
        }

        interface PlayerBulletHitEventParameters {
            weapon: number;
            victim: Entity;
            pos: altShared.Vector3;
        }

        interface PlayerWeaponChangeEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerStartEnterVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerStartLeaveVehicleEventParameters {
            oldWeapon: number;
            newWeapon: number;
        }

        interface GameEntityCreateEventParameters {
            entity: Entity;
        }

        interface GameEntityDestroyEventParameters {
            entity: Entity;
        }

        interface EntityHitEntityEventParameters {
            entity: Entity;
            damager: Entity;
            weapon: number;
        }

        interface TaskChangeEventParameters {
            oldTask: number;
            newTask: number;
        }

        interface KeyUpDownEventParameters {
            key: altShared.Enums.KeyCode;
        }

        interface KeyBoardEventParameters {
            key: altShared.Enums.KeyCode;
            state: altShared.Enums.KeyState;
        }

        interface WebViewEventParameters {
            target: WebView;
            name: string;
            args: unknown[];
        }

        interface WebSocketEventParameters {
            target: WebSocketClient;
            name: string;
            args: unknown[];
        }

        interface AudioEventParameters {
            target: Audio;
            name: string;
            args: unknown[];
        }

        interface RmluiEventParameters {
            target: RmlElement;
            name: string;
            args: unknown[];
        }

        interface WindowFocusChangeEventParameters {
            state: boolean;
        }

        interface WindowResolutionChangeEventParameters {
            oldResolution: altShared.Vector2;
            newResolution: altShared.Vector2;
        }

        // SHARED Entity related events
        export function onBaseObjectCreate(callback: GenericEventCallback<BaseObjectCreateEventParameters>): void;
        export function onBaseObjectRemove(callback: GenericEventCallback<BaseObjectRemoveEventParameters>): void;
        export function onNetOwnerChange(callback: GenericEventCallback<NetOwnerChangeEventParameters>): void;
        export function onWeaponDamage(callback: GenericEventCallback<WeaponDamageEventParameters>): void;

        // SHARED meta related events
        export function onLocalMetaChange(callback: GenericPlayerEventCallback<LocalMetaChangeEventParameters>): void;
        export function onSyncedMetaChange(callback: GenericEventCallback<SyncedMetaChangeEventParameters>): void;
        export function onStreamSyncedMetaChange(callback: GenericEventCallback<StreamSyncedMetaChangeEventParameters>): void;
        export function onGlobalMetaChange(callback: GenericEventCallback<GlobalMetaChangeEventParameters>): void;
        export function onGlobalSyncedMetaChange(callback: GenericEventCallback<GlobalSyncedMetaChangeEventParameters>): void;

        // SHARED custom events
        export function onConsoleCommand(callback: GenericEventCallback<ConsoleCommandEventParameters>): void;
        export function onError(callback: GenericEventCallback<ErrorEventParameters>): void;

        // SHARED script related events
        export function onServerScriptEvent(callback: GenericPlayerEventCallback<ServerScriptEventParameters>): void;
        export function onPlayerScriptEvent(callback: GenericEventCallback<PlayerScriptEventParameters>): void;

        // SHARED resource events
        export function onResourceStart(callback: GenericEventCallback<ResourceStartEventParameters>): void;
        export function onResourceStop(callback: GenericEventCallback<ResourceStopEventParameters>): void;
        export function onResourceError(callback: GenericEventCallback<ResourceErrorEventParameters>): void;

        // SHARED Player events
        interface PlayerAnimationChangeEventParameters {
            oldAnimDict: number;
            newAnimDict: number;
            oldAnimName: number;
            newAnimName: number;
        }

        interface PlayerEnteredVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerEnteringVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerLeftVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerChangeVehicleSeatEventParameters {
            vehicle: Vehicle;
            oldSeat: number;
            newSeat: number;
        }

        interface ServerScriptEventParameters {
            eventName: string;
            args: unknown[];
        }

        interface PlayerScriptEventParameters {
            eventName: string;
            args: unknown[];
        }

        interface BaseObjectCreateEventParameters {
            object: altShared.BaseObject;
        }

        interface BaseObjectRemoveEventParameters {
            object: altShared.BaseObject;
        }

        interface NetOwnerChangeEventParameters {
            entity: Entity;
            oldOwner?: Player;
            newOwner?: Player;
        }

        interface WeaponDamageEventParameters {
            source: Player;
            target: Entity;
            weaponHash: number;
            damage: number;
            offset: number;
            bodyPart: altShared.Enums.BodyPart;

            setDamageValue(value: number): void;
        }

        interface LocalMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface SyncedMetaChangeEventParameters {
            entity: Entity;
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface StreamSyncedMetaChangeEventParameters {
            entity: Entity;
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface GlobalMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface GlobalSyncedMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface ConsoleCommandEventParameters {
            command: string;
            args: string[];
        }

        interface ErrorEventParameters {
            error: string;
            stack: string;
        }

        interface ResourceStartEventParameters {
            resource: altShared.Resource;
        }

        interface ResourceStopEventParameters {
            resource: altShared.Resource;
        }

        interface ResourceErrorEventParameters {
            resource: altShared.Resource;
        }

        type GenericPlayerEventCallback<T> = (params: T & { player: Player }) => void | Promise<void>;
        type GenericEventCallback<T = {}> = (params: T) => void | Promise<void>;
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
        export function set(statName: altShared.Enums.StatName, value: number | boolean | string): void;
        export function get(statName: altShared.Enums.StatName): number | boolean | string | undefined;
        export function reset(statName: altShared.Enums.StatName): void;
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
        export function get(flag: altShared.Enums.ConfigFlag): boolean;
        export function set(flag: altShared.Enums.ConfigFlag, state: boolean): boolean;
        export function exists(flag: altShared.Enums.ConfigFlag): boolean;
    }

    export * from "@altv/shared";
}
