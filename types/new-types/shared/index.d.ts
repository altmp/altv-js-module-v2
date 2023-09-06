/**
 * @module @altv/shared
 */

declare module "@altv/shared" {
    export const isClient: boolean;
    export const isServer: boolean;
    export const isDebug: boolean;
    export const version: string;
    export const branch: string;

    export const meta: Record<string, unknown>;

    export function log(...args: unknown[]): void;
    export function logWarning(...args: unknown[]): void;
    export function logError(...args: unknown[]): void;
    export function sha256(str: string): string;
    export function getVoiceConnectionState(): Enums.VoiceConnectionState;
    export function hash(value: string): number;

    export abstract class BaseObject {
        readonly id: number;
        readonly type: number;

        readonly valid: boolean;
        destroy(): void;

        meta: Record<string, unknown>;

        static getByID(id: number): BaseObject | null;
    }

    export abstract class VoiceChannel extends BaseObject {}

    export abstract class Blip {
        readonly global: boolean;
        readonly isAttached: boolean;
        readonly attachedTo?: Entity;
        blipType: Enums.BlipType;
        scale: Vector2;
        display: number;
        sprite: number;
        color: number;
        secondaryColor: number;
        alpha: number;
        flashTimer: number;
        flashInterval: number;
        friendly: boolean;

        route: boolean;
        bright: boolean;
        number: number;
        showCone: boolean;
        flashes: boolean;
        flashesAlternate: boolean;
        shortRange: boolean;
        priority: number;
        rotation: number;
        gxtName: string;
        name: string;
        routeColor: RGBA;
        pulse: boolean;
        missionCreator: boolean;
        tickVisible: boolean;
        headingIndicatorVisible: boolean;
        outlineIndicatorVisible: boolean;
        friendIndicatorVisible: boolean;
        crewIndicatorVisible: boolean;
        category: number;
        highDetail: boolean;
        shrinked: boolean;
        visible: boolean;
        hiddenOnLegend: boolean;
        minimalOnEdge: boolean;
        useHeightIndicatorOnEdge: boolean;
        shortHeightThreshold: boolean;

        attachTo(entity: Entity): boolean;
        fade(opacity: number, duration: number): void;
    }

    export class Buffer {
        readonly size: number;

        constructor(sizeOrBuffer: number | ArrayBuffer | ArrayBufferView);

        readUInt8(size: number): number;
        readUInt16(size: number): number;
        readUInt32(size: number): number;
        readUInt64(size: number): number;
        readInt8(size: number): number;
        readInt16(size: number): number;
        readInt32(size: number): number;
        readInt64(size: number): number;
        readFloat(size: number): number;
        readDouble(size: number): number;
        readString(size: number): string;

        writeUInt8(offset: number, value: number): void;
        writeUInt16(offset: number, value: number): void;
        writeUInt32(offset: number, value: number): void;
        writeUInt64(offset: number, value: number): void;
        writeInt8(offset: number, value: number): void;
        writeInt16(offset: number, value: number): void;
        writeInt32(offset: number, value: number): void;
        writeInt64(offset: number, value: number): void;
        writeFloat(offset: number, value: number): void;
        writeDouble(offset: number, value: number): void;
        writeString(offset: number, value: string): void;
    }

    export abstract class Checkpoint extends ColShape {
        checkpointType: number;
        radius: number;
        height: number;
        color: RGBA;
        iconColor: RGBA;
        nextPos: Vector3;
        readonly streamingDistance: number;
        visible: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: Vector3): boolean;

        // TODO (xLuxy): proper typings
        static create(...args: unknown[]): unknown;
    }

    export abstract class ColShape {
        // TODO (xLuxy): proper typings
        static create(...args: unknown[]): unknown;
    }

    export abstract class Entity extends WorldObject {
        get model(): number;
        readonly netOwner?: Player;
        rot: Vector3;
        readonly visible: boolean;

        readonly syncedMeta: Readonly<Record<string, unknown>>;
        readonly streamSyncedMeta: Readonly<Record<string, unknown>>;
    }

    export abstract class Object extends Entity {
        readonly alpha: number;
        readonly textureVariation: number;
        readonly lodDistance: number;
    }

    export abstract class Ped extends Entity {
        readonly health: number;
        readonly maxHealth: number;
        readonly armour: number;
        readonly currentWeapon: number;
    }

    export abstract class Player extends Entity {
        readonly name: string;

        readonly health: number;
        readonly maxHealth: number;
        readonly currentWeaponComponents: ReadonlyArray<number>;
        readonly currentWeaponTintIndex: number;
        get currentWeapon(): number;
        readonly isDead: boolean;
        readonly isJumping: boolean;
        readonly isInRagdoll: boolean;
        readonly isAiming: boolean;
        readonly isShooting: boolean;
        readonly isReloading: boolean;
        readonly isEnteringVehicle: boolean;
        readonly isLeavingVehicle: boolean;
        readonly isOnLadder: boolean;
        readonly isInMelee: boolean;
        readonly isInCover: boolean;
        readonly armour: number;
        readonly maxArmour: number;
        readonly moveSpeed: number;
        readonly aimPos: Vector3;
        readonly headRotation: Vector3;
        readonly isInVehicle: boolean;
        readonly vehicle?: Vehicle;
        readonly seat: number;
        readonly entityAimingAt: Entity;
        readonly entityAimOffset: Vector3;
        readonly isFlashlightActive: boolean;
        readonly isSuperJumpEnabled: boolean;
        readonly isCrouching: boolean;
        readonly isStealthy: boolean;
        readonly currentAnimationDict: number;
        readonly currentAnimationName: number;
        readonly isSpawned: boolean;
        readonly forwardSpeed: number;
        readonly strafeSpeed: number;

        getWeaponTintIndex(weaponHash: number | string): number | undefined;
        hasWeaponComponent(weaponHash: number | string, componentHash: number | string): boolean;
    }

    export abstract class Resource {
        readonly type: string;
        readonly path: string;
        readonly name: string;
        readonly main: string;

        readonly exports: Readonly<Record<string, unknown>>;
        readonly dependencies: ReadonlyArray<string>;
        readonly dependants: ReadonlyArray<string>;
        readonly isStarted: boolean;

        readonly config: Readonly<Record<string, unknown>>;

        static readonly current: Resource;
        static readonly all: ReadonlyArray<Resource>;

        static get(resourceName: string): Resource | null;
        static exists(resourceName: string): boolean;
    }

    export abstract class Vehicle extends Entity {
        readonly neon: Readonly<NeonState>;

        readonly driver?: Player;
        readonly isDestroyed: boolean;
        readonly modKitsCount: number;
        readonly modKit: number;
        readonly IsPrimaryColorRGB: boolean;
        readonly primaryColor: number;
        readonly primaryColorRGB: RGBA;
        readonly isSecondaryColorRGB: boolean;
        readonly secondaryColor: number;
        readonly secondaryColorRGB: RGBA;
        readonly pearlColor: number;
        readonly wheelColor: number;
        readonly interiorColor: number;
        readonly dashboardColor: number;
        readonly isTireSmokeColorCustom: boolean;
        readonly tireSmokeColor: RGBA;
        readonly wheelType: number;
        readonly wheelVariation: number;
        readonly customTires: boolean;
        readonly specialDarkness: number;
        readonly numberplateIndex: number;
        readonly numberplateText: string;
        readonly windowTint: number;
        readonly dirtLevel: number;
        readonly isNeonActive: boolean;
        readonly neonColor: RGBA;
        readonly livery: number;
        readonly roofLivery: number;
        readonly appearanceDataBase64: string;
        readonly isEngineOn: boolean;
        readonly isHandbrakeActive: boolean;
        readonly headlightColor: number;
        readonly radioStationIndex: number;
        readonly isSirenActive: boolean;
        readonly lockState: number;
        readonly isDaylightOn: boolean;
        readonly isNightlightOn: boolean;
        readonly roofState: number;
        readonly isFlamethrowerActive: boolean;
        readonly lightsMultiplier: number;
        readonly gameStateBase64: string;
        readonly engineHealth: number;
        readonly petrolTankHealth: number;
        readonly wheelsCount: number;
        readonly repairsCount: number;
        readonly bodyHealth: number;
        readonly bodyAdditionalHealth: number;
        readonly hasArmoredWindows: boolean;
        readonly damageDataBase64: string;
        readonly isManualEngineControl: boolean;
        readonly scriptDataBase64: string;
        readonly velocity: Vector3;
        readonly steeringAngle: number;

        getMod(category: number): number;
        getModsCount(category: number): number;
        isExtraOn(extraId: number): boolean;
        getDoorState(doorId: number): number;
        isWindowOpened(windowId: number): boolean;
        isWheelBurst(wheelId: number): boolean;
        getWheelHasTire(wheelId: number): boolean;
        isWheelDetached(wheelId: number): boolean;
        isWheelOnFire(wheelId: number): boolean;
        getWheelHealth(wheelId: number): number;

        getPartDamageLevel(partId: number): number;
        getPartBulletHoles(partId: number): number;

        isLightDamaged(lightId: number): boolean;
        isWindowDamaged(windowId: number): boolean;

        isSpecialLightDamaged(specialLightId: number): boolean;
        getArmoredWindowHealth(windowId: number): number;
        getArmoredWindowShootCount(windowId: number): number;
        getBumperDamageLevel(bumperId: number): number;
        toggleExtra(extraId: number, state: boolean): void;
    }

    export abstract class VirtualEntity extends WorldObject {
        readonly group: VirtualEntityGroup;
        readonly streamingDistance: number;

        visible: boolean;

        readonly streamSyncedMeta: Record<string, unknown>;

        // TODO (xLuxy): proper typings
        static create(...args: unknown[]): VirtualEntity;
    }

    export abstract class VirtualEntityGroup extends BaseObject {
        readonly maxEntitiesInStream: number;

        // TODO (xLuxy): proper typings
        static create(...args: unknown[]): VirtualEntityGroup;
    }

    export abstract class WorldObject extends BaseObject {
        readonly pos: Vector3;
    }

    export interface IRGBA {
        r: number;
        g: number;
        b: number;
        a?: number;
    }

    export class RGBA {
        readonly r: number;
        readonly g: number;
        readonly b: number;
        readonly a: number;

        constructor(r: number, g: number, b: number, a?: number);
        constructor(rgba: [number, number, number, number | undefined]);
        constructor(rgba: IRGBA);

        toArray(): [number, number, number, number | undefined];
        toInt(): number;

        static readonly zero: RGBA;

        static fromInt(color: number): RGBA;
    }

    class VectorBase<T extends VectorBase<T>> {
        toArray(): number[];
        toFixed(digits?: number): T;

        get length(): number;
        get lengthSquared(): number;
        get negative(): T;
        get inverse(): T;
        get normalized(): T;

        toDegrees(): T;
        toRadians(): T;
    }

    export interface IVector2 {
        x: number;
        y: number;
    }

    export class Vector2 extends VectorBase<Vector2> {
        readonly x: number;
        readonly y: number;

        constructor(value: number);
        constructor(x: number, y: number);
        constructor(xy: [number, number]);
        constructor(xy: IVector2);

        add(x: number, y: number): Vector2;
        add(other: Vector2): Vector2;
        add(xy: [number, number]): Vector2;
        add(xy: IVector2): Vector2;

        sub(x: number, y: number): Vector2;
        sub(other: Vector2): Vector2;
        sub(xy: [number, number]): Vector2;
        sub(xy: IVector2): Vector2;

        mul(x: number, y: number): Vector2;
        mul(other: Vector2): Vector2;
        mul(xy: [number, number]): Vector2;
        mul(xy: IVector2): Vector2;

        div(x: number, y: number): Vector2;
        div(other: Vector2): Vector2;
        div(xy: [number, number]): Vector2;
        div(xy: IVector2): Vector2;

        dot(x: number, y: number): Vector2;
        dot(other: Vector2): Vector2;
        dot(xy: [number, number]): Vector2;
        dot(xy: IVector2): Vector2;

        distanceTo(x: number, y: number): number;
        distanceTo(other: Vector2): number;
        distanceTo(xy: [number, number]): number;
        distanceTo(xy: IVector2): number;

        distanceToSquared(x: number, y: number): number;
        distanceToSquared(other: Vector2): number;
        distanceToSquared(xy: [number, number]): number;
        distanceToSquared(xy: IVector2): number;

        angleTo(x: number, y: number, z: number): number;
        angleTo(other: Vector2): number;
        angleTo(xy: [number, number]): number;
        angleTo(xy: IVector2): number;

        angleToDegrees(x: number, y: number, z: number): number;
        angleToDegrees(other: Vector2): number;
        angleToDegrees(xy: [number, number]): number;
        angleToDegrees(xy: IVector2): number;

        isInRange(range: number, x: number, y: number, z: number): boolean;
        isInRange(range: number, other: Vector2): boolean;
        isInRange(range: number, xy: [number, number]): boolean;
        isInRange(range: number, xy: IVector2): boolean;

        lerp(ratio: number, x: number, y: number, z: number): boolean;
        lerp(ratio: number, other: Vector2): boolean;
        lerp(ratio: number, xy: [number, number]): boolean;
        lerp(ratio: number, xy: IVector2): boolean;

        static zero: Vector2;
        static one: Vector2;
        static up: Vector2;
        static down: Vector2;
        static left: Vector2;
        static right: Vector2;
        static negativeInfinity: Vector2;
        static positiveInfinity: Vector2;

        static fromArray(xy: [number, number]): Vector2;
        static fromObject(xy: IVector2): Vector2;
    }

    export interface IVector3 {
        x: number;
        y: number;
        z: number;
    }

    export class Vector3 extends VectorBase<Vector3> {
        readonly x: number;
        readonly y: number;
        readonly z: number;

        constructor(value: number);
        constructor(x: number, y: number, z: number);
        constructor(xyz: [number, number, number]);
        constructor(xyz: IVector3);

        add(x: number, y: number, z: number): Vector3;
        add(other: Vector3): Vector3;
        add(xyz: [number, number, number]): Vector3;
        add(xyz: IVector3): Vector3;

        sub(x: number, y: number, z: number): Vector3;
        sub(other: Vector3): Vector3;
        sub(xyz: [number, number]): Vector3;
        sub(xyz: IVector3): Vector3;

        mul(x: number, y: number, z: number): Vector3;
        mul(other: Vector3): Vector3;
        mul(xyz: [number, number, number]): Vector3;
        mul(xyz: IVector3): Vector3;

        div(x: number, y: number, z: number): Vector3;
        div(other: Vector3): Vector3;
        div(xyz: [number, number, number]): Vector3;
        div(xyz: IVector3): Vector3;

        dot(x: number, y: number, z: number): Vector3;
        dot(other: Vector3): Vector3;
        dot(xyz: [number, number, number]): Vector3;
        dot(xyz: IVector3): Vector3;

        distanceTo(x: number, y: number, z: number): number;
        distanceTo(other: Vector3): number;
        distanceTo(xyz: [number, number, number]): number;
        distanceTo(xyz: IVector3): number;

        distanceToSquared(x: number, y: number, z: number): number;
        distanceToSquared(other: Vector3): number;
        distanceToSquared(xyz: [number, number, number]): number;
        distanceToSquared(xyz: IVector3): number;

        angleTo(x: number, y: number, z: number): number;
        angleTo(other: Vector3): number;
        angleTo(xyz: [number, number, number]): number;
        angleTo(xyz: IVector3): number;

        angleToDegrees(x: number, y: number, z: number): number;
        angleToDegrees(other: Vector3): number;
        angleToDegrees(xyz: [number, number, number]): number;
        angleToDegrees(xyz: IVector3): number;

        isInRange(range: number, x: number, y: number, z: number): boolean;
        isInRange(range: number, other: Vector3): boolean;
        isInRange(range: number, xyz: [number, number, number]): boolean;
        isInRange(range: number, xyz: IVector3): boolean;

        lerp(ratio: number, x: number, y: number, z: number): boolean;
        lerp(ratio: number, other: Vector3): boolean;
        lerp(ratio: number, xyz: [number, number, number]): boolean;
        lerp(ratio: number, xyz: IVector3): boolean;

        static zero: Vector3;
        static one: Vector3;
        static back: Vector3;
        static up: Vector3;
        static down: Vector3;
        static forward: Vector3;
        static left: Vector3;
        static right: Vector3;
        static negativeInfinity: Vector3;
        static positiveInfinity: Vector3;

        static fromArray(xyz: [number, number, number]): Vector3;
        static fromObject(xyz: IVector3): Vector3;
    }

    export interface WeaponInfo {
        hash: number;
        tintIndex: number;
        components: ReadonlyArray<number>;
    }

    export interface AmmoData {
        ammoHash: number;
        infiniteAmmo: boolean;
        addSmokeOnExplosion: boolean;
        fuse: boolean;
        fixedAfterExplosion: boolean;
    }

    export interface NeonState {
        readonly left: boolean;
        readonly right: boolean;
        readonly front: boolean;
        readonly back: boolean;
    }

    export interface KeyStateInfo {
        isDown: boolean;
        isToggled: boolean;
    }

    export interface WeatherCycle {
        weather: Enums.Weather;
        multiplier: number;
    }

    export interface TimerLocation {
        fileName: string;
        lineNumber: number;
    }

    export interface IQuaternion {
        x: number;
        y: number;
        z: number;
        w: number;
    }

    export class Quaternion {
        constructor(x: number, y: number, z: number, w: number);
        constructor(xyzw: [number, number, number, number]);
        constructor(xyzw: IQuaternion);

        readonly length: number;
        readonly lengthSquared: number;
        readonly conjugate: Quaternion;
        readonly inverse: Quaternion;
        readonly normalized: Quaternion;

        readonly pitch: number;
        readonly yaw: number;
        readonly roll: number;

        readonly eulerAngles: Vector3;
        readonly axis: Vector3;
        readonly angle: number;
        readonly matrix: number[];
        readonly forward: Vector3;
        readonly right: Vector3;
        readonly up: Vector3;
        readonly left: Vector3;
        readonly back: Vector3;
        readonly down: Vector3;

        static fromEuler(x: number, y: number, z: number): Quaternion;
        static fromAxisAngle(axis: Vector3, angle: number): Quaternion;
        static fromMatrix(matrix: number[]): Quaternion;
        static fromArray(xyzw: [number, number, number, number]): Quaternion;
    }

    export namespace Appearance {
        interface HeadOverlay {
            index: number;
            opacity: number;
            colorType: number;
            colorIndex: number;
            secondColorIndex: number;
        }

        interface Clothing {
            drawable: number;
            texture: number;
            palette: number;
        }
        type DlcClothing = Clothing & { dlc: number };

        interface Prop {
            drawable: number;
            texture: number;
        }
        type DlcProp = Prop & { dlc: number };

        interface HeadBlendData {
            shapeFirstID: number;
            shapeSecondID: number;
            shapeThirdID: number;
            skinFirstID: number;
            skinSecondID: number;
            skinThirdID: number;
            shapeMix: number;
            skinMix: number;
            thirdMix: number;
        }
    }

    export namespace Timers {
        export class Interval extends Timer {
            constructor(callback: Function, interval: number);
        }

        export class Timeout extends Timer {
            constructor(callback: Function, interval: number);
        }

        export class EveryTick extends Timer {
            constructor(callback: Function);
        }

        export class NextTick extends Timer {
            constructor(callback: Function);
        }

        export const all: ReadonlyArray<Timer>;

        export let warningThreshold: number;
        export let sourceLocationFrameSkipCount: number;

        export function setInterval(callback: Function, interval: number): Interval;
        export function setTimeout(callback: Function, interval: number): Timeout;
        export function everyTick(callback: Function): EveryTick;
        export function nextTick(callback: Function): NextTick;

        export type TimerType = "Interval" | "Timeout" | "EveryTick" | "NextTick";
    }

    export namespace Utils {
        // export function inspect(): void;

        export function wait(ms: number): Promise<void>;
        export function waitForNextTick(): Promise<void>;
        export function getCurrentSourceLocation(): void;

        export abstract class AssertionError extends Error {}

        export function assert(condition: unknown, message?: string): void;
    }

    export namespace Factory {
        // TODO (xLuxy): types might be wrong?
        type EntityFactorySetter<T extends Entity> = (factory: new () => T) => void;
        type EntityFactoryGetter<T extends Entity> = () => new () => T;

        export function setPlayerFactory(factory: EntityFactorySetter<Player>): void;
        export function getPlayerFactory(): EntityFactoryGetter<Player>;

        export function setVehicleFactory(factory: EntityFactorySetter<Vehicle>): unknown;
        export function getVehicleFactory(): EntityFactoryGetter<Vehicle>;

        export function setPedFactory(factory: EntityFactorySetter<Ped>): unknown;
        export function getPedFactory(): EntityFactoryGetter<Ped>;

        export function setBlipFactory(factory: EntityFactorySetter<Blip>): unknown;
        export function getBlipFactory(): EntityFactoryGetter<Blip>;

        export function setVoiceChannelFactory(factory: EntityFactorySetter<VoiceChannel>): unknown;
        export function getVoiceChannelFactory(): EntityFactoryGetter<VoiceChannel>;

        export function setColShapeFactory(factory: EntityFactorySetter<ColShape>): unknown;
        export function getColShapeFactory(): EntityFactoryGetter<ColShape>;

        export function setObjectFactory(factory: EntityFactorySetter<Object>): unknown;
        export function getObjectFactory(): EntityFactoryGetter<Object>;

        export function setCheckpointFactory(factory: EntityFactorySetter<Checkpoint>): unknown;
        export function getCheckpointFactory(): EntityFactoryGetter<Checkpoint>;

        export function setVirtualEntityFactory(factory: EntityFactorySetter<VirtualEntity>): unknown;
        export function getVirtualEntityFactory(): EntityFactoryGetter<VirtualEntity>;

        export function setVirtualEntityGroupFactory(factory: EntityFactorySetter<VirtualEntityGroup>): unknown;
        export function getVirtualEntityGroupFactory(): EntityFactoryGetter<VirtualEntityGroup>;
    }

    export namespace Commands {
        export type CommandCallback = (args: string[]) => void;

        export function register(commandName: string, callback: CommandCallback): void;
        export function unregister(commandName: string, callback: CommandCallback): void;
    }

    export namespace File {
        export function exists(path: string): boolean;
        export function read(path: string): string;
    }

    export namespace Enums {
        export const enum AmmoSpecialType {
            None,
            ArmorPiercing,
            Explosive,
            FullMetalJacket,
            HollowPoint,
            Incendiary,
            Tracer
        }

        export const enum ColShapeType {
            Sphere,
            Cylinder,
            Circle,
            Cuboid,
            Rectangle,
            CheckpointCylinder,
            Polygon
        }

        export const enum BlipType {
            Vehicle = 1,
            Ped,
            Object,
            Destination,
            Cont,
            PickupUnk,
            Radius,
            Pickup,
            Cop,
            Area,
            Gallery,
            PickupObject
        }

        export const enum KeyCode {
            Key0 = 48,
            Key1 = 49,
            Key2 = 50,
            Key3 = 51,
            Key4 = 52,
            Key5 = 53,
            Key6 = 54,
            Key7 = 55,
            Key8 = 56,
            Key9 = 57,
            Backspace = 8,
            Tab = 9,
            Clear = 12,
            Enter = 13,
            Return = 13,
            Escape = 27,
            Space = 32,
            Left = 37,
            Up = 38,
            Right = 39,
            Down = 40,
            Delete = 46,
            Insert = 45,
            Home = 36,
            End = 35,
            PageUp = 33,
            PageDown = 34,
            CapsLock = 20,
            Shift = 16,
            Alt = 18,
            Ctrl = 17,
            "-" = 189,
            "=" = 187,
            "," = 188,
            ";" = 186,
            "." = 190,
            "/" = 191,
            "`" = 192,
            "~" = 192,
            "'" = 222,
            "[" = 219,
            "]" = 221,
            "\\" = 220,
            KpMultiply = 106,
            KpAdd = 107,
            KpSubtract = 109,
            KpDecimal = 110,
            KpDivide = 111,
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,
            F1 = 112,
            F2 = 113,
            F3 = 114,
            F4 = 115,
            F5 = 116,
            F6 = 117,
            F7 = 118,
            F8 = 119,
            F9 = 120,
            F10 = 121,
            F11 = 122,
            F12 = 123,
            F13 = 124,
            F14 = 125,
            F15 = 126,
            F16 = 127,
            F17 = 128,
            F18 = 129,
            F19 = 130,
            F20 = 131,
            Numpad0 = 96,
            Numpad1 = 97,
            Numpad2 = 98,
            Numpad3 = 99,
            Numpad4 = 100,
            Numpad5 = 101,
            Numpad6 = 102,
            Numpad7 = 103,
            Numpad8 = 104,
            Numpad9 = 105,
            MouseLeft = 1,
            MouseRight = 2,
            MouseMiddle = 4
        }

        export const enum Weather {
            ExtraSunny = 0,
            Clear = 1,
            Clouds = 2,
            Smog = 3,
            Foggy = 4,
            Overcast = 5,
            Rain = 6,
            Thunder = 7,
            LightRain = 8,
            SmoggyLightRain = 9,
            VeryLightSnow = 10,
            WindyLightSnow = 11,
            LightSnow = 12,
            Christmas = 13,
            Halloween = 14
        }

        export const enum Permission {
            None,
            ScreenCapture,
            WebRTC,
            ClipboardAccess,
            ExtendedVoiceAPI,
            All
        }

        export const enum Locale {
            Arabic = "ar",
            Belarusian = "by",
            Czech = "cz",
            German = "de",
            English = "en",
            Spanish = "es",
            Farsi = "fa",
            French = "fr",
            Hebrew = "he",
            Hungarian = "hu",
            Indonesian = "id",
            Hindi = "in_hd", // Wrong tag (hi_in)
            Malayalam = "in_ml", // Wrong tag (ml_in)
            Telugu = "in_tl", // Wrong tag (te_in)
            Tamil = "in_tm", // Wrong tag (ta_in)
            Italian = "it",
            Lithuanian = "lt",
            Latvian = "lv",
            NorwegianBokmal = "nb_no",
            NorwegianNynorsk = "nn_no",
            Polish = "pl",
            Portugese = "pt",
            BrazilianPortuguese = "pt_br",
            Romanian = "ro",
            Serbian = "rs", // Wrong tag (sr)
            Russian = "ru",
            Slovak = "sk",
            Thai = "th",
            Turkish = "tr",
            Ukrainian = "ua", // Wrong tag (uk)
            ChineseSimplified = "zh_cn",
            ChineseTraditional = "zh_tw"
        }

        export const enum BaseObjectType {
            Player,
            Vehicle,
            Ped,
            Object,
            Blip,
            Webview,
            VoiceChannel,
            Colshape,
            Checkpoint,
            WebsocketClient,
            HttpClient,
            Audio,
            AudioOutput,
            AudioOutputWorld,
            AudioOutputAttached,
            AudioOutputFrontend,
            RmlElement,
            RmlDocument,
            LocalPlayer,
            LocalObject,
            VirtualEntity,
            VirtualEntityGroup,
            Marker,
            TextLabel,
            LocalPed,
            LocalVehicle,
            AudioFilter,
            ConnectionInfo,
            CustomTexture,
            Font
        }

        export const enum VoiceConnectionState {
            Disconnected,
            Connecting,
            Connected
        }

        export const enum ExplosionType {
            Unknown = -1,
            Grenade,
            GrenadeLauncher,
            StickyBomb,
            Molotov,
            Rocket,
            TankShell,
            HiOctane,
            Car,
            Plane,
            PetrolPump,
            Bike,
            DirSteam,
            DirFlame,
            DirWaterHydrant,
            DirGasCanister,
            Boat,
            ShipDestroy,
            Truck,
            Bullet,
            SmokeGrenadeLauncher,
            SmokeGrenade,
            BZGas,
            Flare,
            GasCanister,
            Extinquisher,
            ProgrammableAR,
            Train,
            Barrel,
            Propane,
            Blimp,
            DirFlameExplode,
            Tanker,
            PlaneRocket,
            VehicleBullet,
            GasTank,
            Firework,
            Snowball,
            ProxMine,
            ValkyrieCannon
        }

        export const enum BlipType {
            Vehicle = 1,
            Ped = 2,
            Object = 3,
            Destination = 4,
            Cont = 5,
            PickupUnk = 6,
            Radius = 7,
            Pickup = 8,
            Cop = 9,
            Area = 11,
            Gallery = 12,
            PickupObject = 13
        }

        export const enum ColShapeType {
            Sphere,
            Cylinder,
            Circle,
            Cuboid,
            Rect,
            CheckpointCylinder,
            Polygon
        }

        export const enum VehicleModelType {
            Invalid,
            Ped,
            Automobile,
            Plane,
            Trailer,
            QuadBike,
            SubmarineCar,
            AmphibiousAutomobile,
            AmphibiousQuadBike,
            Heli,
            Blimp,
            Autogyro,
            Bike,
            BMX,
            Boat,
            Train,
            Submarine,
            Object
        }

        export const enum BodyPart {
            Unknown = -1,
            Pelvis,
            LeftHip,
            LeftLeg,
            LeftFoot,
            RightHip,
            RightLeg,
            RightFoot,
            LowerTorso,
            UpperTorso,
            Chest,
            UnderNeck,
            LeftShoulder,
            LeftUpperArm,
            LeftElbrow,
            LeftWrist,
            RightShoulder,
            RightUpperArm,
            RightElbrow,
            RightWrist,
            Neck,
            Head
        }

        export const enum EventType {
            // Server
            ServerStarted = 1,
            ClientRequestObjectEvent,
            ClientDeleteObjectEvent,

            // Shared
            PlayerConnect,
            PlayerDisconnect,
            PlayerConnectDenied,
            PlayerSpawn,

            ConnectionQueueAdd,
            ConnectionQueueRemove,

            ResourceStart,
            ResourceStop,
            ResourceError,

            ServerScriptEvent,
            ClientScriptEvent,

            MetaChange,
            SyncedMetaChange,
            StreamSyncedMetaChange,
            GlobalMetaChange,
            GlobalSyncedMetaChange,
            LocalSyncedMetaChange,

            PlayerDamage,
            PlayerDeath,
            PlayerHeal,
            FireEvent,
            ExplosionEvent,
            StartProjectileEvent,
            WeaponDamageEvent,
            VehicleDestroy,
            VehicleDamage,

            RequestSyncedScene,
            StartSyncedScene,
            StopSyncedScene,
            UpdateSyncedScene,

            CheckpointEvent,
            ColshapeEvent,
            PlayerEnterVehicle,
            PlayerStartEnterVehicle,
            PlayerEnteringVehicle,
            PlayerLeaveVehicle,
            PlayerStartLeaveVehicle,
            PlayerChangeVehicleSeat,
            PlayerWeaponChange,
            PlayerRequestControl,

            VehicleAttach,
            VehicleDetach,
            VehicleHorn,
            VehicleSiren,
            NetownerChange,

            CreateBaseObjectEvent,
            RemoveBaseObjectEvent,

            DataNodeReceivedEvent,

            ConsoleCommandEvent,

            PlayerChangeAnimationEvent,

            PlayerChangeInteriorEvent,

            PlayerWeaponShootEvent,
            PlayerBulletHitEvent,

            PlayerDimensionChange,

            // Client
            ConnectionComplete,
            DisconnectEvent,
            WebViewEvent,
            KeyboardEvent,
            GameEntityCreate,
            GameEntityDestroy,
            WebSocketClientEvent,
            AudioEvent,
            TaskChange,
            Spawned,
            RmlUiEvent,
            WindowFocusChange,
            WindowResolutionChange,
            EntityHitEntity,

            WorldObjectPositionChange,
            WorldObjectStreamIn,
            WorldObjectStreamOut,

            VoiceConnectionEvent
        }

        export const enum CustomEventType {
            EntityEnterColshape = 1,
            EntityLeaveColshape,
            EntityEnterCheckpoint,
            EntityLeaveCheckpoint,
            Error,
            KeyUp,
            KeyDown
        }

        export const enum MetricType {
            Gauge,
            Counter
        }

        export const enum KeyState {
            Up,
            Down
        }
    }

    export namespace PointBlip {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace AreaBlip {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace RadiusBlip {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapeSphere {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapeCylinder {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapeCircle {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapeCuboid {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapeRectangle {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }

    export namespace ColShapePolygon {
        // TODO (xLuxy): proper typings
        export function create(...args: unknown[]): unknown;
    }
}

declare abstract class Timer {
    public interval: number;
    public callback: Function;
    public lastTick: number;
    public once?: boolean;
    public location: TimerLocation;

    public get type(): import("@altv/shared").Timers.TimerType;

    public destroy(): void;
}
