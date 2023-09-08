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
        readonly type: Enums.BaseObjectType;

        readonly valid: boolean;
        destroy(): void;

        readonly meta: Record<string, unknown>;

        static getByID(type: Enums.BaseObjectType, id: number): BaseObject | null;
    }

    export abstract class VoiceChannel extends BaseObject {}

    export abstract class Blip extends BaseObject {
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

        static getByID(id: number): Blip | null;
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

    interface CheckpointCreateOptions {
        type: Enums.CheckpointType;
        pos: IVector3;
        radius: number;
        height: number;
        color: RGBA;
        streamingDistance: number;
    }

    // @ts-ignore - Suppresses "Class static side incorrectly extends base class static side"
    export abstract class Checkpoint extends ColShape {
        checkpointType: number;
        radius: number;
        height: number;
        color: RGBA;
        iconColor: RGBA;
        nextPos: IVector3;
        readonly streamingDistance: number;
        visible: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: Vector3): boolean;

        static create(opts: CheckpointCreateOptions): Checkpoint | null;
        static getByID(id: number): Checkpoint | null;
    }

    interface ColShapeSphereCreateOptions {
        pos: IVector3;
        radius: number;
    }

    interface ColShapeCylinderCreateOptions {
        pos: IVector3;
        radius: number;
        height: number;
    }

    interface ColShapeCircleCreateOptions {
        pos: IVector2;
        radius: number;
    }

    interface ColShapeCuboidCreateOptions {
        pos1: IVector2;
        pos2: IVector3;
    }

    interface ColShapeRectangleCreateOptions {
        x1: number;
        y1: number;
        x2: number;
        y2: number;
    }

    interface ColShapePolygonCreateOptions {
        minZ: number;
        maxZ: number;
        points: IVector2[];
    }

    type ColShapeCreateOptions = {
        colShapeType: Enums.ColShapeType;
    } & (
        | ({ colShapeType: Enums.ColShapeType.SPHERE } & ColShapeSphereCreateOptions)
        | ({ colShapeType: Enums.ColShapeType.CYLINDER } & ColShapeCylinderCreateOptions)
        | ({ colShapeType: Enums.ColShapeType.CIRCLE } & ColShapeCircleCreateOptions)
        | ({ colShapeType: Enums.ColShapeType.CUBOID } & ColShapeCuboidCreateOptions)
        | ({ colShapeType: Enums.ColShapeType.RECT } & ColShapeRectangleCreateOptions)
        | ({ colShapeType: Enums.ColShapeType.POLYGON } & ColShapePolygonCreateOptions)
    );

    export abstract class ColShape extends WorldObject {
        readonly colShapeType: Enums.ColShapeType;
        playersOnly: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: Vector3): boolean;

        static create(opts: ColShapeCreateOptions): ColShape | null;
        static getByID(id: number): ColShape | null;
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

        static getByID(id: number): Object | null;
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

        static getByID(id: number): Player | null;
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

    interface VirtualEntityCreateOptions {
        group: VirtualEntityGroup;
        pos: IVector3;
        maxEntitiesInStream: number;
        data?: Record<string, unknown>;
    }

    export abstract class VirtualEntity extends WorldObject {
        readonly group: VirtualEntityGroup;
        readonly streamingDistance: number;

        visible: boolean;

        readonly streamSyncedMeta: Record<string, unknown>;

        static create(opts: VirtualEntityCreateOptions): VirtualEntity | null;
    }

    interface VirtualEntityGroupCreateOptions {
        streamingRangeLimit: number;
    }

    export abstract class VirtualEntityGroup extends BaseObject {
        readonly maxEntitiesInStream: number;

        static create(opts: VirtualEntityGroupCreateOptions): VirtualEntityGroup | null;
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

    export interface SourceLocation {
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
        static fromAxisAngle(axis: IVector3, angle: number): Quaternion;
        static fromMatrix(matrix: number[]): Quaternion;
        static fromArray(xyzw: [number, number, number, number]): Quaternion;
    }

    export type PointBlipCreateOptions = { pos: IVector3; entity?: never } | { entity: Entity; pos?: never };

    export interface AreaBlipCreateOptions {
        pos: IVector3;
        scale: IVector2;
    }

    export interface RadiusBlipCreateOptions {
        pos: IVector3;
        radius: number;
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
        // boolean = showHidden
        export function inspect(value: unknown, options?: boolean | Partial<InspectOptions>): void;

        export function wait(ms: number): Promise<void>;
        export function waitForNextTick(): Promise<void>;
        export function getCurrentSourceLocation(): SourceLocation;

        export abstract class AssertionError extends Error {}

        export function assert(condition: unknown, message?: string): void;

        export interface InspectOptions {
            showHidden: boolean; // default: false
            depth: number; // default: 2
            colors: boolean; // default: false
            customInspect: boolean; // default: true
            showProxy: boolean; // default: false
            maxArrayLength: number; // default: 100
            maxStringLength: number; // default: 10000
            breakLength: number; // default: 80
            compact: number; // default: 3
            sorted: boolean; // default: false
            getters: boolean; // default: false
            numericSeparator: boolean; // default: false
        }
    }

    export namespace Factory {
        export function setPlayerFactory(factory: typeof Player): void;
        export function getPlayerFactory<T extends Player>(): T;

        export function setVehicleFactory(factory: typeof Vehicle): void;
        export function getVehicleFactory<T extends Vehicle>(): T;

        export function setPedFactory(factory: typeof Ped): void;
        export function getPedFactory<T extends Ped>(): T;

        export function setBlipFactory(factory: typeof Blip): void;
        export function getBlipFactory<T extends Blip>(): T;

        // TODO (xLuxy): Server-only - find a better way to extend namespaces and move this into server typings
        export function setVoiceChannelFactory(factory: typeof VoiceChannel): void;
        export function getVoiceChannelFactory<T extends VoiceChannel>(): T;

        export function setColShapeFactory(factory: typeof ColShape): void;
        export function getColShapeFactory<T extends ColShape>(): T;

        export function setObjectFactory(factory: typeof Object): void;
        export function getObjectFactory<T extends Object>(): T;

        export function setCheckpointFactory(factory: typeof Checkpoint): void;
        export function getCheckpointFactory<T extends Checkpoint>(): T;

        export function setVirtualEntityFactory(factory: typeof VirtualEntity): void;
        export function getVirtualEntityFactory<T extends VirtualEntity>(): T;

        export function setVirtualEntityGroupFactory(factory: typeof VirtualEntityGroup): void;
        export function getVirtualEntityGroupFactory<T extends VirtualEntityGroup>(): T;
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
            NONE,
            ARMOR_PIERCING,
            EXPLOSIVE,
            FULL_METAL_JACKET,
            HOLLOW_POINT,
            INCENDIARY,
            TRACER
        }

        export const enum ColShapeType {
            SPHERE,
            CYLINDER,
            CIRCLE,
            CUBOID,
            RECT,
            CHECKPOINT_CYLINDER,
            POLYGON
        }

        export const enum BlipType {
            VEHICLE = 1,
            PED = 2,
            OBJECT = 3,
            DESTINATION = 4,
            CONT = 5,
            PICKUP_UNK = 6,
            RADIUS = 7,
            PICKUP = 8,
            COP = 9,
            AREA = 11,
            GALLERY = 12,
            PICKUP_OBJECT = 13
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
            NONE,
            SCREEN_CAPTURE,
            WEBRTC,
            CLIPBOARD_ACCESS,
            EXTENDED_VOICE_API,
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
            PLAYER,
            VEHICLE,
            PED,
            OBJECT,
            BLIP,
            WEBVIEW,
            VOICE_CHANNEL,
            COLSHAPE,
            CHECKPOINT,
            WEBSOCKET_CLIENT,
            HTTP_CLIENT,
            AUDIO,
            AUDIO_OUTPUT,
            AUDIO_OUTPUT_WORLD,
            AUDIO_OUTPUT_ATTACHED,
            AUDIO_OUTPUT_FRONTEND,
            RML_ELEMENT,
            RML_DOCUMENT,
            LOCAL_PLAYER,
            LOCAL_OBJECT,
            VIRTUAL_ENTITY,
            VIRTUAL_ENTITY_GROUP,
            MARKER,
            TEXT_LABEL,
            LOCAL_PED,
            LOCAL_VEHICLE,
            AUDIO_FILTER,
            CONNECTION_INFO,
            CUSTOM_TEXTURE,
            FONT,
            SIZE
        }

        export const enum VoiceConnectionState {
            DISCONNECTED,
            CONNECTING,
            CONNECTED
        }

        export const enum ExplosionType {
            GRENADE,
            GRENADELAUNCHER,
            STICKYBOMB,
            MOLOTOV,
            ROCKET,
            TANKSHELL,
            HI_OCTANE,
            CAR,
            PLANE,
            PETROL_PUMP,
            BIKE,
            DIR_STEAM,
            DIR_FLAME,
            DIR_WATER_HYDRANT,
            DIR_GAS_CANISTER,
            BOAT,
            SHIP_DESTROY,
            TRUCK,
            BULLET,
            SMOKEGRENADELAUNCHER,
            SMOKEGRENADE,
            BZGAS,
            FLARE,
            GAS_CANISTER,
            EXTINGUISHER,
            PROGRAMMABLEAR,
            TRAIN,
            BARREL,
            PROPANE,
            BLIMP,
            DIR_FLAME_EXPLODE,
            TANKER,
            PLANE_ROCKET,
            VEHICLE_BULLET,
            GAS_TANK,
            FIREWORK,
            SNOWBALL,
            PROXMINE,
            VALKYRIE_CANNON,

            UNKNOWN = -1
        }

        export const enum VehicleModelType {
            INVALID,
            PED,
            AUTOMOBILE,
            PLANE,
            TRAILER,
            QUAD_BIKE,
            SUBMARINE_CAR,
            AMPHIBIOUS_AUTOMOBILE,
            AMPHIBIOUS_QUAD_BIKE,
            HELI,
            BLIMP,
            AUTOGYRO,
            BIKE,
            BMX,
            BOAT,
            TRAIN,
            SUBMARINE,
            OBJECT
        }

        export const enum BodyPart {
            PELVIS,
            LEFT_HIP,
            LEFT_LEG,
            LEFT_FOOT,
            RIGHT_HIP,
            RIGHT_LEG,
            RIGHT_FOOT,
            LOWER_TORSO,
            UPPER_TORSO,
            CHEST,
            UNDER_NECK,
            LEFT_SHOULDER,
            LEFT_UPPER_ARM,
            LEFT_ELBROW,
            LEFT_WRIST,
            RIGHT_SHOULDER,
            RIGHT_UPPER_ARM,
            RIGHT_ELBROW,
            RIGHT_WRIST,
            NECK,
            HEAD,

            UNKNOWN = -1
        }

        export const enum EventType {
            NONE,

            // Server
            SERVER_STARTED,
            CLIENT_REQUEST_OBJECT_EVENT,
            CLIENT_DELETE_OBJECT_EVENT,

            // Shared
            PLAYER_CONNECT,
            PLAYER_DISCONNECT,
            PLAYER_CONNECT_DENIED,
            PLAYER_SPAWN,

            CONNECTION_QUEUE_ADD,
            CONNECTION_QUEUE_REMOVE,

            RESOURCE_START,
            RESOURCE_STOP,
            RESOURCE_ERROR,

            SERVER_SCRIPT_EVENT,
            CLIENT_SCRIPT_EVENT,

            META_CHANGE,
            SYNCED_META_CHANGE,
            STREAM_SYNCED_META_CHANGE,
            GLOBAL_META_CHANGE,
            GLOBAL_SYNCED_META_CHANGE,
            LOCAL_SYNCED_META_CHANGE,

            PLAYER_DAMAGE,
            PLAYER_DEATH,
            PLAYER_HEAL,
            FIRE_EVENT,
            EXPLOSION_EVENT,
            START_PROJECTILE_EVENT,
            WEAPON_DAMAGE_EVENT,
            VEHICLE_DESTROY,
            VEHICLE_DAMAGE,

            REQUEST_SYNCED_SCENE,
            START_SYNCED_SCENE,
            STOP_SYNCED_SCENE,
            UPDATE_SYNCED_SCENE,

            CHECKPOINT_EVENT,
            COLSHAPE_EVENT,
            PLAYER_ENTER_VEHICLE,
            PLAYER_START_ENTER_VEHICLE,
            PLAYER_ENTERING_VEHICLE,
            PLAYER_LEAVE_VEHICLE,
            PLAYER_START_LEAVE_VEHICLE,
            PLAYER_CHANGE_VEHICLE_SEAT,
            PLAYER_WEAPON_CHANGE,
            PLAYER_REQUEST_CONTROL,

            VEHICLE_ATTACH,
            VEHICLE_DETACH,
            VEHICLE_HORN,
            VEHICLE_SIREN,
            NETOWNER_CHANGE,

            CREATE_BASE_OBJECT_EVENT,
            REMOVE_BASE_OBJECT_EVENT,

            DATA_NODE_RECEIVED_EVENT,

            CONSOLE_COMMAND_EVENT,

            PLAYER_CHANGE_ANIMATION_EVENT,

            PLAYER_CHANGE_INTERIOR_EVENT,

            PLAYER_WEAPON_SHOOT_EVENT,
            PLAYER_BULLET_HIT_EVENT,

            PLAYER_DIMENSION_CHANGE,

            // Client
            CONNECTION_COMPLETE,
            DISCONNECT_EVENT,
            WEB_VIEW_EVENT,
            KEYBOARD_EVENT,
            GAME_ENTITY_CREATE,
            GAME_ENTITY_DESTROY,
            WEB_SOCKET_CLIENT_EVENT,
            AUDIO_EVENT,
            TASK_CHANGE,
            SPAWNED,
            RMLUI_EVENT,
            WINDOW_FOCUS_CHANGE,
            WINDOW_RESOLUTION_CHANGE,
            ENTITY_HIT_ENTITY,

            WORLD_OBJECT_POSITION_CHANGE,
            WORLD_OBJECT_STREAM_IN,
            WORLD_OBJECT_STREAM_OUT,

            VOICE_CONNECTION_EVENT,

            ALL,
            SIZE
        }

        export const enum CustomEventType {
            NONE,

            ENTITY_ENTER_COLSHAPE,
            ENTITY_LEAVE_COLSHAPE,
            ENTITY_ENTER_CHECKPOINT,
            ENTITY_LEAVE_CHECKPOINT,
            ERROR,
            KEY_UP,
            KEY_DOWN,

            SIZE
        }

        export const enum MetricType {
            METRIC_TYPE_GAUGE,
            METRIC_TYPE_COUNTER,
            METRIC_TYPE_SIZE
        }

        export const enum KeyState {
            UP,
            DOWN
        }

        export const enum WatermarkPosition {
            BottomRight = 0,
            TopRight = 1,
            TopLeft = 2,
            TopCenter = 3,
            BottomCenter = 4
        }

        export const enum StatName {
            Stamina = "stamina",
            Strength = "strength",
            LungCapacity = "lung_capacity",
            Wheelie = "wheelie_ability",
            Flying = "flying_ability",
            Shooting = "shooting_ability",
            Stealth = "stealth_ability"
        }

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

        export const enum CheckpointType {
            CylinderSingleArrow,
            CylinderDoubleArrow,
            CylinderTripleArrow,
            CylinderCycleArrow,
            CylinderCheckerboard,
            CylinderWrench,
            CylinderSingleArrow2,
            CylinderDoubleArrow2,
            CylinderTripleArrow2,
            CylinderCycleArrow2,
            CylinderCheckerboard2,
            CylinderWrench2,
            RingSingleArrow,
            RingDoubleArrow,
            RingTripleArrow,
            RingCycleArrow,
            RingCheckerboard,
            SingleArrow,
            DoubleArrow,
            TripleArrow,
            CycleArrow,
            Checkerboard,
            CylinderSingleArrow3,
            CylinderDoubleArrow3,
            CylinderTripleArrow3,
            CylinderCycleArrow3,
            CylinderCheckerboard3,
            CylinderSingleArrow4,
            CylinderDoubleArrow4,
            CylinderTripleArrow4,
            CylinderCycleArrow4,
            CylinderCheckerboard4,
            CylinderSingleArrow5,
            CylinderDoubleArrow5,
            CylinderTripleArrow5,
            CylinderCycleArrow5,
            CylinderCheckerboard5,
            RingPlaneUp,
            RingPlaneLeft,
            RingPlaneRight,
            RingPlaneDown,
            Empty,
            Ring,
            Empty2,
            Cylinder,
            Cylinder1,
            Cylinder2,
            Cylinder3,
            Cylinder4,
            Cylinder5,
            Empty3,
            Empty4,
            Empty5,
            Empty6,
            RingDollar,
            RingWolf,
            RingQuestionMark,
            RingPlane,
            RingChopper,
            RingBoat,
            RingCar,
            RingBike,
            RingBicycle,
            RingTruck,
            RingParachute,
            RingJetpack,
            RingWhirl
        }
    }

    export namespace ColShapeSphere {
        export function create(opts: ColShapeSphereCreateOptions): ColShape | null;
    }

    export namespace ColShapeCylinder {
        export function create(opts: ColShapeCylinderCreateOptions): ColShape | null;
    }

    export namespace ColShapeCircle {
        export function create(opts: ColShapeCircleCreateOptions): ColShape | null;
    }

    export namespace ColShapeCuboid {
        export function create(opts: ColShapeCuboidCreateOptions): ColShape | null;
    }

    export namespace ColShapeRectangle {
        export function create(opts: ColShapeRectangleCreateOptions): ColShape | null;
    }

    export namespace ColShapePolygon {
        export function create(opts: ColShapePolygonCreateOptions): ColShape | null;
    }
}

declare abstract class Timer {
    public interval: number;
    public callback: Function;
    public lastTick: number;
    public once?: boolean;
    public location: import("@altv/shared").SourceLocation;

    public get type(): import("@altv/shared").Timers.TimerType;

    public destroy(): void;
}
