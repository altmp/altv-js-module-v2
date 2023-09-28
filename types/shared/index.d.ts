/**
 * @module @altv/shared
 */

declare module "@altv/shared" {
    export const isClient: boolean;
    export const isServer: boolean;
    export const isDebug: boolean;
    export const version: string;
    export const sdkVersion: string;
    export const branch: string;

    export const meta: GlobalMeta;
    export const syncedMeta: GlobalSyncedMeta;

    export function log(...args: unknown[]): void;
    export function logWarning(...args: unknown[]): void;
    export function logError(...args: unknown[]): void;
    export function sha256(str: string): string;
    export function getVoiceConnectionState(): Enums.VoiceConnectionState;
    export function getNetTime(): number;
    export function hash(value: string): number;

    export abstract class BaseObject {
        readonly id: number;
        readonly type: Enums.BaseObjectType;

        readonly valid: boolean;
        destroy(): void;

        static getByID(type: Enums.BaseObjectType, id: number): BaseObject | null;
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

    interface VirtualEntityGroupCreateOptions {
        maxEntitiesInStream: number;
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
        add(xy: number): Vector2;

        sub(x: number, y: number): Vector2;
        sub(other: Vector2): Vector2;
        sub(xy: [number, number]): Vector2;
        sub(xy: IVector2): Vector2;
        sub(xy: number): Vector2;

        mul(x: number, y: number): Vector2;
        mul(other: Vector2): Vector2;
        mul(xy: [number, number]): Vector2;
        mul(xy: IVector2): Vector2;
        mul(xy: number): Vector2;

        div(x: number, y: number): Vector2;
        div(other: Vector2): Vector2;
        div(xy: [number, number]): Vector2;
        div(xy: IVector2): Vector2;
        div(xy: number): Vector2;

        dot(x: number, y: number): Vector2;
        dot(other: Vector2): Vector2;
        dot(xy: [number, number]): Vector2;
        dot(xy: IVector2): Vector2;
        dot(xy: number): Vector2;

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
        add(xyz: number): Vector3;

        sub(x: number, y: number, z: number): Vector3;
        sub(other: Vector3): Vector3;
        sub(xyz: [number, number]): Vector3;
        sub(xyz: IVector3): Vector3;
        sub(xyz: number): Vector3;

        mul(x: number, y: number, z: number): Vector3;
        mul(other: Vector3): Vector3;
        mul(xyz: [number, number, number]): Vector3;
        mul(xyz: IVector3): Vector3;
        mul(xyz: number): Vector3;

        div(x: number, y: number, z: number): Vector3;
        div(other: Vector3): Vector3;
        div(xyz: [number, number, number]): Vector3;
        div(xyz: IVector3): Vector3;
        div(xyz: number): Vector3;

        dot(x: number, y: number, z: number): Vector3;
        dot(other: Vector3): Vector3;
        dot(xyz: [number, number, number]): Vector3;
        dot(xyz: IVector3): Vector3;
        dot(xyz: number): Vector3;

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

    export interface AreaBlipCreateOptions {
        pos: IVector3;
        scale: IVector2;
    }

    export interface RadiusBlipCreateOptions {
        pos: IVector3;
        radius: number;
    }

    /**
     * Extend it by interface merging for use in {@link meta alt.meta}.
     */
    export interface GlobalMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in {@link syncedMeta alt.syncedMeta}.
     */
    export interface GlobalSyncedMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in BaseObject#syncedMeta.
     */
    export interface BaseObjectSyncedMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in Blip#syncedMeta.
     */
    export interface BlipSyncedMeta extends BaseObjectSyncedMeta {}

    /**
     * Extend it by interface merging for use in ColShape#syncedMeta.
     */
    export interface ColShapeSyncedMeta extends BaseObjectSyncedMeta {}

    /**
     * Extend it by interface merging for use in Checkpoint#syncedMeta.
     */
    export interface CheckpointSyncedMeta extends ColShapeSyncedMeta {}

    /**
     * Extend it by interface merging for use in Checkpoint#streamSyncedMeta.
     */
    export interface CheckpointStreamSyncedMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in Entity#syncedMeta.
     */
    export interface EntitySyncedMeta extends BaseObjectSyncedMeta {}

    /**
     * Extend it by interface merging for use in Entity#streamSyncedMeta.
     */
    export interface EntityStreamSyncedMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in Player#syncedMeta.
     */
    export interface PlayerSyncedMeta extends EntitySyncedMeta {}

    /**
     * Extend it by interface merging for use in Player#streamSyncedMeta.
     */
    export interface PlayerStreamSyncedMeta extends EntityStreamSyncedMeta {}

    /**
     * Extend it by interface merging for use in Vehicle#syncedMeta.
     */
    export interface VehicleSyncedMeta extends EntitySyncedMeta {}

    /**
     * Extend it by interface merging for use in Vehicle#streamSyncedMeta.
     */
    export interface VehicleStreamSyncedMeta extends EntityStreamSyncedMeta {}

    /**
     * Extend it by interface merging for use in Object#syncedMeta.
     */
    export interface ObjectSyncedMeta extends EntitySyncedMeta {}

    /**
     * Extend it by interface merging for use in Object#streamSyncedMeta.
     */
    export interface ObjectStreamSyncedMeta extends EntityStreamSyncedMeta {}

    /**
     * Extend it by interface merging for use in VirtualEntity#streamSyncedMeta.
     */
    export interface VirtualEntitySyncedMeta extends BaseObjectSyncedMeta {}

    /**
     * Extend it by interface merging for use in VirtualEntity#syncedMeta.
     */
    export interface VirtualEntityStreamSyncedMeta extends BaseObjectSyncedMeta {}

    /**
     * Extend it by interface merging for use in Ped#syncedMeta.
     */
    export interface PedSyncedMeta extends EntitySyncedMeta {}

    /**
     * Extend it by interface merging for use in ped stream synced meta (class `Ped` on client & server, e.g. `ped.getStreamSyncedMeta`)
     */
    export interface PedStreamSyncedMeta extends EntityStreamSyncedMeta {}

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
            constructor(callback: Function, interval: number, ...args: unknown[]);
        }

        export class Timeout extends Timer {
            constructor(callback: Function, interval: number, ...args: unknown[]);
        }

        export class EveryTick extends Timer {
            constructor(callback: Function, ...args: unknown[]);
        }

        export class NextTick extends Timer {
            constructor(callback: Function, ...args: unknown[]);
        }

        export const all: ReadonlyArray<Timer>;

        export let warningThreshold: number;
        export let sourceLocationFrameSkipCount: number;

        export function setInterval(callback: Function, interval: number, ...args: unknown[]): Interval;
        export function setTimeout(callback: Function, interval: number, ...args: unknown[]): Timeout;
        export function everyTick(callback: Function, ...args: unknown[]): EveryTick;
        export function nextTick(callback: Function, ...args: unknown[]): NextTick;

        export function time(name?: string): void;
        export function timeEnd(name?: string): void;

        export function getByID(id: number): Timer | null;
    }

    export namespace Utils {
        // boolean = showHidden
        export function inspect(value: unknown, options?: boolean | Partial<InspectOptions>): void;

        export function wait(ms: number): Promise<void>;
        export function waitForNextTick(): Promise<void>;
        export function waitFor(callback: () => boolean, timeout?: number): Promise<void>;
        export function getCurrentSourceLocation(): SourceLocation;

        // TODO (xLuxy): Shared type fuckery
        export function addLocalMetaListener(key: string, callback: Function): Events.EventHandler;
        export function addSyncedMetaListener(key: string, callback: Function): Events.EventHandler;
        export function addStreamSyncedMetaListener(key: string, callback: Function): Events.EventHandler;

        export abstract class AssertionError extends Error {}

        export type JSType = "string" | "number" | "object" | "function" | "undefined" | "boolean" | "symbol" | "bigint";

        export function assert(condition: unknown, message?: string): void;
        export function assertIsObject(value: unknown, message?: string): void;
        export function assertIsType(value: unknown, type: JSType, message?: string): void;

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

    export namespace Commands {
        export type CommandCallback = (args: string[]) => void;

        export function register(commandName: string, callback: CommandCallback): void;
        export function unregister(commandName: string, callback: CommandCallback): void;
    }

    export namespace File {
        export function exists(path: string): boolean;
        export function read(path: string): string;
    }

    export namespace Events {
        interface CustomRemoteEvent {}
        interface CustomPlayerToServerEvent {}
        interface CustomServerToPlayerEvent {}
        interface CustomClientToWebViewEvent {}

        interface WebViewToClientEvent {
            load(): void;
        }
        interface CustomWebViewToClientEvent extends WebViewToClientEvent {}

        interface GenericOnEventCallback {
            readonly [key: string]: unknown;
            readonly customEvent: boolean;
        }

        export class EventHandler {
            readonly eventType: Enums.EventType | Enums.CustomEventType;
            readonly eventTypeName: string;
            readonly handler: Function;
            readonly location: SourceLocation;
            readonly onlyOnce: boolean;
            readonly valid: boolean;

            destroy(): void;
        }

        export class ScriptEventHandler extends EventHandler {
            readonly eventName: string;
            readonly local: boolean;
            readonly remote: boolean;
        }

        export class GenericEventHandler extends EventHandler {}
    }

    export namespace Enums {
        export enum AmmoSpecialType {
            NONE,
            ARMOR_PIERCING,
            EXPLOSIVE,
            FULL_METAL_JACKET,
            HOLLOW_POINT,
            INCENDIARY,
            TRACER
        }

        export enum ColShapeType {
            SPHERE,
            CYLINDER,
            CIRCLE,
            CUBOID,
            RECT,
            CHECKPOINT_CYLINDER,
            POLYGON
        }

        export enum BlipSprite {
            HIGHER,
            LOWER,
            POLICE_PED,
            WANTED_RADIUS,
            AREA,
            CENTRE,
            NORTH,
            WAYPOINT,
            RADIUS,
            RADIUS_OUTLINE,
            WEAPON_HIGHER,
            WEAPON_LOWER,
            HIGHER_AI,
            LOWER_AI,
            POLICE_HELI_SPIN,
            POLICE_PLANE_MOVE,
            MP_CREW = 27,
            MP_FRIENDLIES,
            CABLE_CAR = 36,
            ACTIVITIES,
            RACEFLAG,
            SAFEHOUSE = 40,
            POLICE,
            POLICE_CHASE,
            POLICE_HELI,
            BOMB_A,
            SNITCH = 47,
            PLANNING_LOCATIONS,
            CRIMINAL_CARSTEAL = 50,
            CRIMINAL_DRUGS,
            CRIMINAL_HOLDUPS,
            CRIMINAL_PLAYER = 54,
            COP_PATROL = 56,
            COP_PLAYER,
            CRIMINAL_WANTED,
            HEIST,
            POLICE_STATION,
            HOSPITAL,
            ASSASSINS_MARK,
            ELEVATOR,
            HELICOPTER,
            RANDOM_CHARACTER = 66,
            SECURITY_VAN,
            TOW_TRUCK,
            ILLEGAL_PARKING = 70,
            BARBER,
            CAR_MOD_SHOP,
            CLOTHES_STORE,
            TATTOO = 75,
            ARMENIAN_FAMILY,
            LESTER_FAMILY,
            MICHAEL_FAMILY,
            TREVOR_FAMILY,
            JEWELRY_HEIST,
            DRAG_RACE_FINISH = 82,
            RAMPAGE = 84,
            VINEWOOD_TOURS,
            LAMAR_FAMILY,
            FRANKLIN_FAMILY = 88,
            CHINESE_STRAND,
            FLIGHT_SCHOOL,
            EYE_SKY,
            AIR_HOCKEY,
            BAR,
            BASE_JUMP,
            BASKETBALL,
            BIOLAB_HEIST = 96,
            CABARET_CLUB = 99,
            CAR_WASH,
            COMEDY_CLUB = 102,
            DARTS,
            DOCKS_HEIST,
            FBI_HEIST,
            FBI_OFFICERS_STRAND,
            FINALE_BANK_HEIST,
            FINANCIER_STRAND,
            GOLF,
            GUN_SHOP,
            INTERNET_CAFE,
            MICHAEL_FAMILY_EXILE,
            NICE_HOUSE_HEIST,
            RANDOM_FEMALE,
            RANDOM_MALE,
            RURAL_BANK_HEIST = 118,
            SHOOTING_RANGE,
            SOLOMON_STRAND,
            STRIP_CLUB,
            TENNIS,
            TREVOR_FAMILY_EXILE,
            MICHAEL_TREVOR_FAMILY,
            TRIATHLON = 126,
            OFF_ROAD_RACING,
            GANG_COPS,
            GANG_MEXICANS,
            GANG_BIKERS,
            SNITCH_RED = 133,
            CRIMINAL_CUFF_KEYS,
            CINEMA,
            MUSIC_VENUE,
            POLICE_STATION_BLUE,
            AIRPORT,
            CRIMINAL_SAVED_VEHICLE,
            WEED_STASH,
            HUNTING,
            POOL,
            OBJECTIVE_BLUE,
            OBJECTIVE_GREEN,
            OBJECTIVE_RED,
            OBJECTIVE_YELLOW,
            ARMS_DEALING,
            MP_FRIEND,
            CELEBRITY_THEFT,
            WEAPON_ASSAULT_RIFLE,
            WEAPON_BAT,
            WEAPON_GRENADE,
            WEAPON_HEALTH,
            WEAPON_KNIFE,
            WEAPON_MOLOTOV,
            WEAPON_PISTOL,
            WEAPON_ROCKET,
            WEAPON_SHOTGUN,
            WEAPON_SMG,
            WEAPON_SNIPER,
            MP_NOISE,
            POINT_OF_INTEREST,
            PASSIVE,
            USING_MENU,
            GANG_COPS_PARTNER = 171,
            WEAPON_MINIGUN = 173,
            WEAPON_ARMOUR = 175,
            PROPERTY_TAKEOVER,
            GANG_MEXICANS_HIGHLIGHT,
            GANG_BIKERS_HIGHLIGHT,
            TRIATHLON_CYCLING,
            TRIATHLON_SWIMMING,
            PROPERTY_TAKEOVER_BIKERS,
            PROPERTY_TAKEOVER_COPS,
            PROPERTY_TAKEOVER_VAGOS,
            CAMERA,
            CENTRE_RED,
            HANDCUFF_KEYS_BIKERS,
            HANDCUFF_KEYS_VAGOS,
            HANDCUFFS_CLOSED_BIKERS,
            HANDCUFFS_CLOSED_VAGOS,
            CAMERA_BADGER = 192,
            CAMERA_FACADE,
            CAMERA_IFRUIT,
            YOGA = 197,
            TAXI,
            SHRINK = 205,
            EPSILON,
            FINANCIER_STRAND_GREY,
            TREVOR_FAMILY_GREY,
            TREVOR_FAMILY_RED,
            FRANKLIN_FAMILY_GREY,
            FRANKLIN_FAMILY_BLUE,
            FRANKLIN_A,
            FRANKLIN_B,
            FRANKLIN_C,
            GANG_VEHICLE = 225,
            GANG_VEHICLE_BIKERS,
            GANG_VEHICLE_COPS,
            GANG_VEHICLE_VAGOS,
            GUNCAR,
            DRIVING_BIKERS,
            DRIVING_COPS,
            DRIVING_VAGOS,
            GANG_COPS_HIGHLIGHT,
            SHIELD_BIKERS,
            SHIELD_COPS = 235,
            SHIELD_VAGOS,
            CUSTODY_BIKERS,
            CUSTODY_VAGOS,
            ARMS_DEALING_AIR = 251,
            PLAYER_STATE_ARRESTED,
            PLAYER_STATE_CUSTODY,
            PLAYER_STATE_DRIVING,
            PLAYER_STATE_KEYHOLDER,
            PLAYER_STATE_PARTNER,
            ZTYPE = 262,
            STINGER,
            PACKER,
            MONROE,
            FAIRGROUND,
            PROPERTY,
            GANG_HIGHLIGHT,
            ALTRUIST,
            AI,
            ON_MISSION,
            CASH_PICKUP,
            CHOP,
            DEAD,
            TERRITORY_LOCKED,
            CASH_LOST,
            CASH_VAGOS,
            CASH_COPS,
            HOOKER,
            FRIEND,
            MISSION2TO4,
            MISSION2TO8,
            MISSION2TO12,
            MISSION2TO16,
            CUSTODY_DROP_OFF,
            ON_MISSION_COPS,
            ON_MISSION_LOST,
            ON_MISSION_VAGOS,
            CRIMINAL_CAR_STEAL_COPS,
            CRIMINAL_CAR_STEAL_BIKERS,
            CRIMINAL_CAR_STEAL_VAGOS,
            BAND_STRAND,
            SIMEON_FAMILY,
            MISSION1,
            MISSION2,
            FRIEND_DARTS,
            FRIEND_COMEDY_CLUB,
            FRIEND_CINEMA,
            FRIEND_TENNIS,
            FRIEND_STRIP_CLUB,
            FRIEND_LIVE_MUSIC,
            FRIEND_GOLF,
            BOUNTY_HIT,
            UGC_MISSION,
            HORDE,
            CRATE_DROP,
            PLANE_DROP,
            SUB,
            RACE,
            DEATHMATCH,
            ARM_WRESTLING,
            MISSION1TO2,
            SHOOTING_RANGE_GUN_SHOP,
            RACE_AIR,
            RACE_LAND,
            RACE_SEA,
            TOW,
            GARBAGE,
            DRILL,
            SPIKES,
            FIRETRUCK,
            MINIGUN2,
            BUGSTAR,
            SUBMARINE,
            CHINOOK,
            GETAWAY_CAR,
            MISSION_BIKERS1,
            MISSION_BIKERS1TO2,
            MISSION_BIKERS2,
            MISSION_BIKERS2TO4,
            MISSION_BIKERS2TO8,
            MISSION_BIKERS2TO12,
            MISSION_BIKERS2TO16,
            MISSION_COPS1,
            MISSION_COPS1TO2,
            MISSION_COPS2,
            MISSION_COPS2TO4,
            MISSION_COPS2TO8,
            MISSION_COPS2TO12,
            MISSION_COPS2TO16,
            MISSION_VAGOS1,
            MISSION_VAGOS1TO2,
            MISSION_VAGOS2,
            MISSION_VAGOS2TO4,
            MISSION_VAGOS2TO8,
            MISSION_VAGOS2TO12,
            MISSION_VAGOS2TO16,
            GANG_BIKE,
            GAS_GRENADE,
            PROPERTY_FOR_SALE,
            GANG_ATTACK_PACKAGE,
            MARTIN_MADRAZZO,
            ENEMY_HELI_SPIN,
            BOOST,
            DEVIN,
            DOCK,
            GARAGE,
            GOLF_FLAG,
            HANGAR,
            HELIPAD,
            JERRY_CAN,
            MASK,
            HEIST_PREP,
            INCAPACITATED,
            SPAWN_POINT_PICKUP,
            BOILERSUIT,
            COMPLETED,
            ROCKETS,
            GARAGE_FOR_SALE,
            HELIPAD_FOR_SALE,
            DOCK_FOR_SALE,
            HANGAR_FOR_SALE,
            PLACEHOLDER6,
            BUSINESS,
            BUSINESS_FOR_SALE,
            RACE_BIKE,
            PARACHUTE,
            TEAM_DEATHMATCH,
            RACE_FOOT,
            VEHICLE_DEATHMATCH,
            BARRY,
            DOM,
            MARYANN,
            CLETUS,
            JOSH,
            MINUTE,
            OMEGA,
            TONYA,
            PAPARAZZO,
            AIM,
            CRATE_DROP_BACKGROUND,
            GREEN_AND_NET_PLAYER1,
            GREEN_AND_NET_PLAYER2,
            GREEN_AND_NET_PLAYER3,
            GREEN_AND_FRIENDLY,
            NET_PLAYER1_AND_NET_PLAYER2,
            NET_PLAYER1_AND_NET_PLAYER3,
            CREATOR,
            CREATOR_DIRECTION,
            ABIGAIL,
            BLIMP,
            REPAIR,
            TESTOSTERONE,
            DINGHY,
            FANATIC,
            INFO_ICON = 407,
            CAPTURE_THE_FLAG,
            LAST_TEAM_STANDING,
            BOAT,
            CAPTURE_THE_FLAG_BASE,
            CAPTURE_THE_FLAG_OUTLINE = 413,
            CAPTURE_THE_FLAG_BASE_NO_BAG,
            WEAPON_JERRYCAN,
            RP,
            LEVEL_INSIDE,
            BOUNTY_HIT_INSIDE,
            CAPTURE_THE_USA_FLAG,
            CAPTURE_THE_USA_FLAG_OUTLINE,
            TANK,
            PLAYER_HELI,
            PLAYER_PLANE,
            PLAYER_JET,
            CENTRE_STROKE,
            PLAYER_GUN_CAR,
            PLAYER_BOAT,
            MP_HEIST,
            TEMP1,
            TEMP2,
            TEMP3,
            TEMP4,
            TEMP5,
            TEMP6,
            RACE_STUNT,
            HOT_PROPERTY,
            URBAN_WARFARE_VERSUS,
            KING_OF_THE_CASTLE,
            PLAYER_KING,
            DEAD_DROP,
            PENNED_IN,
            BEAST,
            EDGE_POINTER,
            EDGE_CROSS_THE_LINE,
            MP_LAMAR,
            BENNYS,
            CORNER_NUMBER1,
            CORNER_NUMBER2,
            CORNER_NUMBER3,
            CORNER_NUMBER4,
            CORNER_NUMBER5,
            CORNER_NUMBER6,
            CORNER_NUMBER7,
            CORNER_NUMBER8,
            YACHT,
            FINDERS_KEEPERS,
            ASSAULT_PACKAGE,
            HUNT_THE_BOSS,
            SIGHTSEER,
            TURRETED_LIMO,
            BELLY_OF_THE_BEAST,
            YACHT_LOCATION,
            PICKUP_BEAST,
            PICKUP_ZONED,
            PICKUP_RANDOM,
            PICKUP_SLOW_TIME,
            PICKUP_SWAP,
            PICKUP_THERMAL,
            PICKUP_WEED,
            WEAPON_RAILGUN,
            SEASHARK,
            PICKUP_HIDDEN,
            WAREHOUSE,
            WAREHOUSE_FOR_SALE,
            OFFICE,
            OFFICE_FOR_SALE,
            TRUCK,
            CONTRABAND,
            TRAILER,
            VIP,
            CARGOBOB,
            AREA_OUTLINE,
            PICKUP_ACCELERATOR,
            PICKUP_GHOST,
            PICKUP_DETONATOR,
            PICKUP_BOMB,
            PICKUP_ARMOURED,
            STUNT,
            WEAPON_LIVES,
            STUNT_PREMIUM,
            ADVERSARY,
            BIKER_CLUBHOUSE,
            BIKER_CAGED_IN,
            BIKER_TURF_WAR,
            BIKER_JOUST,
            PRODUCTION_WEED,
            PRODUCTION_CRACK,
            PRODUCTION_FAKE_ID,
            PRODUCTION_METH,
            PRODUCTION_MONEY,
            PACKAGE,
            CAPTURE1,
            CAPTURE2,
            CAPTURE3,
            CAPTURE4,
            CAPTURE5,
            CAPTURE6,
            CAPTURE7,
            CAPTURE8,
            CAPTURE9,
            CAPTURE10,
            QUAD,
            BUS,
            DRUGS_PACKAGE,
            PICKUP_JUMP,
            ADVERSARY4,
            ADVERSARY8,
            ADVERSARY10,
            ADVERSARY12,
            ADVERSARY16,
            LAPTOP,
            PICKUP_DEADLINE,
            SPORTS_CAR,
            WAREHOUSE_VEHICLE,
            REG_PAPERS,
            POLICE_STATION_DROPOFF,
            JUNKYARD,
            EX_VECH1,
            EX_VECH2,
            EX_VECH3,
            EX_VECH4,
            EX_VECH5,
            EX_VECH6,
            EX_VECH7,
            TARGET_A,
            TARGET_B,
            TARGET_C,
            TARGET_D,
            TARGET_E,
            TARGET_F,
            TARGET_G,
            TARGET_H,
            JUGGERNAUT,
            PICKUP_REPAIR,
            STEERING_WHEEL,
            TROPHY,
            PICKUP_ROCKET_BOOST,
            PICKUP_HOMING_ROCKET,
            PICKUP_MACHINEGUN,
            PICKUP_PARACHUTE,
            PICKUP_TIME5,
            PICKUP_TIME10,
            PICKUP_TIME15,
            PICKUP_TIME20,
            PICKUP_TIME30,
            SUPPLIES,
            PROPERTY_BUNKER,
            GR_WVM1,
            GR_WVM2,
            GR_WVM3,
            GR_WVM4,
            GR_WVM5,
            GR_WVM6,
            GR_COVERT_OPS,
            ADVERSARY_BUNKER,
            GR_MOC_UPGRADE,
            GR_W_UPGRADE,
            SM_CARGO,
            SM_HANGAR,
            TF_CHECKPOINT,
            RACE_TF,
            SM_WP1,
            SM_WP2,
            SM_WP3,
            SM_WP4,
            SM_WP5,
            SM_WP6,
            SM_WP7,
            SM_WP8,
            SM_WP9,
            SM_WP10,
            SM_WP11,
            SM_WP12,
            SM_WP13,
            SM_WP14,
            NHP_BAG,
            NHP_CHEST,
            NHP_ORBIT,
            NHP_VEH1,
            NHP_BASE,
            NHP_OVERLAY,
            NHP_TURRET,
            NHP_MG_FIREWALL,
            NHP_MG_NODE,
            NHP_WP1,
            NHP_WP2,
            NHP_WP3,
            NHP_WP4,
            NHP_WP5,
            NHP_WP6,
            NHP_WP7,
            NHP_WP8,
            NHP_WP9,
            NHP_CCTV,
            NHP_STARTERPACK,
            NHP_TURRET_CONSOLE,
            NHP_MG_MIR_ROTATE,
            NHP_MG_MIR_STATIC,
            NHP_MG_PROXY,
            ACSR_RACE_TARGET,
            ACSR_RACE_HOTRING,
            ACSR_WP1,
            ACSR_WP2,
            BAT_CLUB_PROPERTY,
            BAT_CARGO,
            BAT_TRUCK,
            BAT_HACK_JEWEL,
            BAT_HACK_GOLD,
            BAT_KEYPAD,
            BAT_HACK_TARGET,
            PICKUP_DTB_HEALTH,
            PICKUP_DTB_BLAST_INCREASE,
            PICKUP_DTB_BLAST_DECREASE,
            PICKUP_DTB_BOMB_INCREASE,
            PICKUP_DTB_BOMB_DECREASE,
            BAT_RIVAL_CLUB,
            BAT_DRONE,
            BAT_CASH_REG,
            CCTV,
            BAT_ASSASSINATE,
            BAT_PBUS,
            BAT_WP1,
            BAT_WP2,
            BAT_WP3,
            BAT_WP4,
            BAT_WP5,
            BAT_WP6,
            BLIMP2,
            OPPRESSOR2,
            BAT_WP7,
            ARENA_SERIES,
            ARENA_PREMIUM,
            ARENA_WORKSHOP,
            RACE_WARS,
            ARENA_TURRET,
            ARENA_RC_CAR,
            ARENA_RC_WORKSHOP,
            ARENA_TRAP_FIRE,
            ARENA_TRAP_FLIP,
            ARENA_TRAP_SEA,
            ARENA_TRAP_TURN,
            ARENA_TRAP_PIT,
            ARENA_TRAP_MINE,
            ARENA_TRAP_BOMB,
            ARENA_TRAP_WALL,
            ARENA_TRAP_BRD,
            ARENA_TRAP_SBRD,
            ARENA_BRUISER,
            ARENA_BRUTUS,
            ARENA_CERBERUS,
            ARENA_DEATHBIKE,
            ARENA_DOMINATOR,
            ARENA_IMPALER,
            ARENA_IMPERATOR,
            ARENA_ISSI,
            ARENA_SASQUATCH,
            ARENA_SCARAB,
            ARENA_SLAMVAN,
            ARENA_ZR,
            AP,
            COMIC_STORE,
            COP_CAR,
            RC_TIME_TRIALS,
            KING_OF_THE_HILL,
            KING_OF_THE_HILL_TEAMS,
            RUCKSACK,
            SHIPPING_CONTAINER,
            AGATHA,
            CASINO,
            CASINO_TABLE_GAMES,
            CASINO_WHEEL,
            CASINO_CONCIERGE,
            CASINO_CHIPS,
            CASINO_HORSE_RACING,
            ADVERSARY_FEATURED,
            ROULETTE1,
            ROULETTE2,
            ROULETTE3,
            ROULETTE4,
            ROULETTE5,
            ROULETTE6,
            ROULETTE7,
            ROULETTE8,
            ROULETTE9,
            ROULETTE10,
            ROULETTE11,
            ROULETTE12,
            ROULETTE13,
            ROULETTE14,
            ROULETTE15,
            ROULETTE16,
            ROULETTE17,
            ROULETTE18,
            ROULETTE19,
            ROULETTE20,
            ROULETTE21,
            ROULETTE22,
            ROULETTE23,
            ROULETTE24,
            ROULETTE25,
            ROULETTE26,
            ROULETTE27,
            ROULETTE28,
            ROULETTE29,
            ROULETTE30,
            ROULETTE31,
            ROULETTE32,
            ROULETTE33,
            ROULETTE34,
            ROULETTE35,
            ROULETTE36,
            ROULETTE0,
            ROULETTE00,
            LIMO,
            WEAPON_ALIEN,
            RACE_OPEN_WHEEL,
            RAPPEL,
            SWAP_CAR,
            SCUBA_GEAR,
            CPANEL1,
            CPANEL2,
            CPANEL3,
            CPANEL4,
            SNOW_TRUCK,
            BUGGY1,
            BUGGY2,
            ZHABA,
            GERALD,
            RON,
            ARCADE,
            DRONE_CONTROLS,
            RC_TANK,
            STAIRS,
            CAMERA2,
            WINKY,
            MINI_SUB,
            KART_RETRO,
            KART_MODERN,
            MILITARY_QUAD,
            MILITARY_TRUCK,
            SHIP_WHEEL,
            UFO,
            SEASPARROW2,
            DINGHY2,
            PATROL_BOAT,
            RETRO_SPORTS_CAR,
            SQUADEE,
            FOLDING_WING_JET,
            VALKYRIE2,
            SUB2,
            BOLT_CUTTERS,
            RAPPEL_GEAR,
            KEY_CARD,
            PASSWORD,
            ISLAND_HEIST_PREP,
            ISLAND_PARTY,
            CONTROL_TOWER,
            UNDERWATER_GATE,
            POWER_SWITCH,
            COMPOUND_GATE,
            RAPPEL_POINT,
            KEY_PAD,
            SUB_CONTROLS,
            SUB_PERISCOPE,
            SUB_MISSILE,
            PAINTING,
            CAR_MEET,
            CAR_TEST_AREA,
            AUTO_SHOP_PROPERTY,
            DOCKS_EXPORT,
            PRIZE_CAR,
            TEST_CAR,
            CAR_ROBBERY_BOARD,
            CAR_ROBBERY_PREP,
            STREET_RACE_SERIES,
            PURSUIT_SERIES,
            CAR_MEET_ORGANISER,
            SECURO_SERV,
            BOUNTY_COLLECTIBLES,
            MOVIE_COLLECTIBLES,
            TRAILER_RAMP,
            RACE_ORGANISER,
            CHALKBOARD_LIST,
            EXPORT_VEHICLE,
            TRAIN,
            HEIST_DIAMOND,
            HEIST_DOOMSDAY,
            HEIST_ISLAND,
            SLAMVAN2,
            CRUSADER,
            CONSTRUCTION_OUTFIT,
            OVERLAY_JAMMED,
            HEIST_ISLAND_UNAVAILABLE,
            HEIST_DIAMOND_UNAVAILABLE,
            HEIST_DOOMSDAY_UNAVAILABLE,
            PLACEHOLDER7,
            PLACEHOLDER8,
            PLACEHOLDER9,
            FEATURED_SERIES,
            VEHICLE_FOR_SALE,
            VAN_KEYS,
            SUV_SERVICE,
            SECURITY_CONTRACT,
            SAFE,
            PED_R,
            PED_E,
            PAYPHONE,
            PATRIOT3,
            MUSIC_STUDIO,
            JUBILEE,
            GRANGER2,
            EXPLOSIVE_CHARGE,
            DEITY,
            D_CHAMPION,
            BUFFALO4,
            AGENCY
        }

        export enum BlipColor {
            WHITE,
            RED,
            GREEN,
            BLUE,
            YELLOW = 5,
            LIGHT_RED,
            VIOLET,
            PINK,
            LIGHT_ORANGE,
            LIGHT_BROWN,
            LIGHT_GREEN,
            LIGHT_BLUE,
            LIGHT_PURPLE,
            DARK_PURPLE,
            CYAN,
            LIGHT_YELLOW,
            ORGANE,
            DARK_PINK = 19,
            GRANITE_GREEN,
            DARK_BROWN,
            LIGHT_GRAY,
            LIGHT_PINK,
            LEMON_GREEN,
            FOREST_GREEN,
            ELECTRIC_BLUE,
            BRIGHT_PURPLE,
            DARK_YELLOW,
            DARK_CYAN = 30,
            BEIGE = 36,
            DARK_GRAY = 40,
            PINK_RED,
            GOLD = 46,
            ORANGE,
            BRILLIANT_ROSE,
            MEDIUM_PURPLE = 50,
            SALMON,
            DARK_GREEN,
            BLIZZARD_BLUE,
            ORACLE_BLUE,
            SILVER,
            EAST_BAY = 58,
            YELLOW_ORANGE = 60,
            MULBERRY_PINK,
            ALTO_GRAY,
            JELLY_BEAN_BLUE,
            DARK_ORANGE,
            MAMBA,
            TRANSPARENT_BLACK = 72,
            DEEP_RED = 76,
            TRANSPARENT_RED = 79,
            TRANSPARENT_BLUE = 80,
            PURPLE = 83
        }

        export enum BlipType {
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

        // When changing, update shared/js/enums/keyCode.js aswell
        export enum KeyCode {
            KEY0 = 48,
            KEY1 = 49,
            KEY2 = 50,
            KEY3 = 51,
            KEY4 = 52,
            KEY5 = 53,
            KEY6 = 54,
            KEY7 = 55,
            KEY8 = 56,
            KEY9 = 57,
            BACKSPACE = 8,
            TAB = 9,
            CLEAR = 12,
            ENTER = 13,
            RETURN = 13,
            ESCAPE = 27,
            SPACE = 32,
            LEFT = 37,
            UP = 38,
            RIGHT = 39,
            DOWN = 40,
            DELETE = 46,
            INSERT = 45,
            HOME = 36,
            END = 35,
            PAGE_UP = 33,
            PAGE_DOWN = 34,
            CAPS_LOCK = 20,
            SHIFT = 16,
            ALT = 18,
            CTRL = 17,
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
            KP_MULTIPLY = 106,
            KP_ADD = 107,
            KP_SUBTRACT = 109,
            KP_DECIMAL = 110,
            KP_DIVIDE = 111,
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
            NUMPAD0 = 96,
            NUMPAD1 = 97,
            NUMPAD2 = 98,
            NUMPAD3 = 99,
            NUMPAD4 = 100,
            NUMPAD5 = 101,
            NUMPAD6 = 102,
            NUMPAD7 = 103,
            NUMPAD8 = 104,
            NUMPAD9 = 105,
            MOUSE_LEFT = 1,
            MOUSE_RIGHT = 2,
            MOUSE_MIDDLE = 4
        }

        // When changing, update shared/js/enums/weather.js aswell
        export enum Weather {
            EXTRA_SUNNY = 0,
            CLEAR = 1,
            CLOUDS = 2,
            SMOG = 3,
            FOGGY = 4,
            OVERCAST = 5,
            RAIN = 6,
            THUNDER = 7,
            LIGHT_RAIN = 8,
            SMOGGY_LIGHT_RAIN = 9,
            VERY_LIGHT_SNOW = 10,
            WINDY_LIGHT_SNOW = 11,
            LIGHT_SNOW = 12,
            CHRISTMAS = 13,
            HALLOWEEN = 14
        }

        export enum Permission {
            NONE,
            SCREEN_CAPTURE,
            WEBRTC,
            CLIPBOARD_ACCESS,
            EXTENDED_VOICE_API,
            All
        }

        // When changing, update shared/js/enums/locale.js aswell
        export enum Locale {
            ARABIC = "ar",
            BELARUSIAN = "by",
            CZECH = "cz",
            GERMAN = "de",
            ENGLISH = "en",
            SPANISH = "es",
            FARSI = "fa",
            FRENCH = "fr",
            HEBREW = "he",
            HUNGARIAN = "hu",
            INDONESIAN = "id",
            HINDI = "in_hd", // Wrong tag (hi_in)
            MALAYALAM = "in_ml", // Wrong tag (ml_in)
            TELUGU = "in_tl", // Wrong tag (te_in)
            TAMIL = "in_tm", // Wrong tag (ta_in)
            ITALIAN = "it",
            LITHUANIAN = "lt",
            LATVIAN = "lv",
            NORWEGIAN_BOKMAL = "nb_no",
            NORWEGIAN_NYNORSK = "nn_no",
            POLISH = "pl",
            PORTUGESE = "pt",
            BRAZILIAN_PORTUGUESE = "pt_br",
            ROMANIAN = "ro",
            SERBIAN = "rs", // Wrong tag (sr)
            RUSSIAN = "ru",
            SLOVAK = "sk",
            THAI = "th",
            TURKISH = "tr",
            UKRAINIAN = "ua", // Wrong tag (uk)
            CHINESE_SIMPLIFIED = "zh_cn",
            CHINESE_TRADITIONAL = "zh_tw"
        }

        export enum BaseObjectType {
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

        export enum VoiceConnectionState {
            DISCONNECTED,
            CONNECTING,
            CONNECTED
        }

        export enum ExplosionType {
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

        export enum VehicleModelType {
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

        export enum BodyPart {
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

        export enum EventType {
            NONE,

            // Server
            SERVER_STARTED,
            CLIENT_REQUEST_OBJECT_EVENT,
            CLIENT_DELETE_OBJECT_EVENT,

            CLIENT_SCRIPT_RPC_EVENT,

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

            COLSHAPE_EVENT,
            PLAYER_ENTER_VEHICLE,
            PLAYER_START_ENTER_VEHICLE,
            PLAYER_ENTERING_VEHICLE,
            PLAYER_LEAVE_VEHICLE,
            PLAYER_START_LEAVE_VEHICLE,
            PLAYER_CHANGE_VEHICLE_SEAT,
            PLAYER_WEAPON_CHANGE,
            PLAYER_REQUEST_CONTROL,
            PLAYER_START_TALKING,
            PLAYER_STOP_TALKING,

            VEHICLE_ATTACH,
            VEHICLE_DETACH,
            VEHICLE_HORN,
            VEHICLE_SIREN,
            NETOWNER_CHANGE,

            CREATE_BASE_OBJECT_EVENT,
            REMOVE_BASE_OBJECT_EVENT,

            CONSOLE_COMMAND_EVENT,

            PLAYER_CHANGE_ANIMATION_EVENT,

            PLAYER_CHANGE_INTERIOR_EVENT,

            PLAYER_WEAPON_SHOOT_EVENT,
            PLAYER_BULLET_HIT_EVENT,

            PLAYER_DIMENSION_CHANGE,

            GIVE_PED_SCRIPTED_TASK,

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

            PED_DAMAGE,
            PED_DEATH,
            PED_HEAL,

            SERVER_SCRIPT_RPC_ANSWER_EVENT,

            ALL,
            SIZE
        }

        export enum CustomEventType {
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

        export enum MetricType {
            METRIC_TYPE_GAUGE,
            METRIC_TYPE_COUNTER,
            METRIC_TYPE_SIZE
        }

        export enum KeyState {
            UP,
            DOWN
        }

        // When changing, update shared/js/enums/watermarkPosition.js aswell
        export enum WatermarkPosition {
            BOTTOM_RIGHT = 0,
            TOP_RIGHT = 1,
            TOP_LEFT = 2,
            TOP_CENTER = 3,
            BOTTOM_CENTER = 4
        }

        // When changing, update shared/js/enums/gameFont.js aswell
        export enum GameFont {
            CHALET_LONDON = 0,
            HOUSE_SCRIPT = 1,
            MONOSPACE = 2,
            CHARLET_COMPRIME_COLONGE = 4,
            PRICEDOWN = 7
        }

        // When changing, update shared/js/enums/statName.js aswell
        export enum StatName {
            STAMINA = "stamina",
            STRENGTH = "strength",
            LUNG_CAPACITY = "lung_capacity",
            WHEELIE = "wheelie_ability",
            FLYING = "flying_ability",
            SHOOTING = "shooting_ability",
            STEALTH = "stealth_ability"
        }

        // When changing, update shared/js/enums/configFlag.js aswell
        export enum ConfigFlag {
            DISABLE_AUTO_WEAPON_SWAP = "DISABLE_AUTO_WEAPON_SWAP",
            DISABLE_PED_PROP_KNOCK_OFF = "DISABLE_PED_PROP_KNOCK_OFF",
            DISABLE_IDLE_CAMERA = "DISABLE_IDLE_CAMERA",
            DISABLE_VEHICLE_ENGINE_SHUTDOWN_ON_LEAVE = "DISABLE_VEHICLE_ENGINE_SHUTDOWN_ON_LEAVE",
            DISABLE_SP_ENTER_VEHICLE_CLIPSET = "DISABLE_SP_ENTER_VEHICLE_CLIPSET",
            FORCE_RENDER_SNOW = "FORCE_RENDER_SNOW",
            FORCE_HIDE_NIGHT_PROPS = "FORCE_HIDE_NIGHT_PROPS",
            FORCE_SHOW_NIGHT_PROPS = "FORCE_SHOW_NIGHT_PROPS",
            DISABLE_EMISSIVE_LIGHTS_RENDERING = "DISABLE_EMISSIVE_LIGHTS_RENDERING"
        }

        // When changing, update shared/js/enums/checkpointType.js aswell
        export enum CheckpointType {
            CYLINDER_SINGLE_ARROW,
            CYLINDER_DOUBLE_ARROW,
            CYLINDER_TRIPLE_ARROW,
            CYLINDER_CYCLE_ARROW,
            CYLINDER_CHECKERBOARD,
            CYLINDER_WRENCH,
            CYLINDER_SINGLE_ARROW2,
            CYLINDER_DOUBLE_ARROW2,
            CYLINDER_TRIPLE_ARROW2,
            CYLINDER_CYCLE_ARROW2,
            CYLINDER_CHECKERBOARD2,
            CYLINDER_WRENCH2,
            RING_SINGLE_ARROW,
            RING_DOUBLE_ARROW,
            RING_TRIPLE_ARROW,
            RING_CYCLE_ARROW,
            RING_CHECKERBOARD,
            SINGLE_ARROW,
            DOUBLE_ARROW,
            TRIPLE_ARROW,
            CYCLE_ARROW,
            CHECKERBOARD,
            CYLINDER_SINGLE_ARROW3,
            CYLINDER_DOUBLE_ARROW3,
            CYLINDER_TRIPLE_ARROW3,
            CYLINDER_CYCLE_ARROW3,
            CYLINDER_CHECKERBOARD3,
            CYLINDER_SINGLE_ARROW4,
            CYLINDER_DOUBLE_ARROW4,
            CYLINDER_TRIPLE_ARROW4,
            CYLINDER_CYCLE_ARROW4,
            CYLINDER_CHECKERBOARD4,
            CYLINDER_SINGLE_ARROW5,
            CYLINDER_DOUBLE_ARROW5,
            CYLINDER_TRIPLE_ARROW5,
            CYLINDER_CYCLE_ARROW5,
            CYLINDER_CHECKERBOARD5,
            RING_PLANE_UP,
            RING_PLANE_LEFT,
            RING_PLANE_RIGHT,
            RING_PLANE_DOWN,
            EMPTY,
            RING,
            EMPTY2,
            CYLINDER,
            CYLINDER1,
            CYLINDER2,
            CYLINDER3,
            CYLINDER4,
            CYLINDER5,
            EMPTY3,
            EMPTY4,
            EMPTY5,
            EMPTY6,
            RING_DOLLAR,
            RING_WOLF,
            RING_QUESTION_MARK,
            RING_PLANE,
            RING_CHOPPER,
            RING_BOAT,
            RING_CAR,
            RING_BIKE,
            RING_BICYCLE,
            RING_TRUCK,
            RING_PARACHUTE,
            RING_JETPACK,
            RING_WHIRL
        }

        export enum TimerType {
            TIMER,
            INTERVAL,
            TIMEOUT,
            EVERY_TICK,
            NEXT_TICK
        }

        export enum TaskTypeIndex {
            HANDS_UP = 0,
            CLIMB_LADDER = 1,
            EXIT_VEHICLE = 2,
            COMBAT_ROLL = 3,
            AIM_GUN_ON_FOOT = 4,
            MOVE_PLAYER = 5,
            PLAYER_ON_FOOT = 6,
            WEAPON = 8,
            PLAYER_WEAPON = 9,
            PLAYER_IDLES = 10,
            AIM_GUN = 12,
            COMPLEX = 12,
            FSM_CLONE = 12,
            MOTION_BASE = 12,
            MOVE = 12,
            MOVE_BASE = 12,
            NM_BEHAVIOUR = 12,
            NAV_BASE = 12,
            SCENARIO = 12,
            SEARCH_BASE = 12,
            SEARCH_IN_VEHICLE_BASE = 12,
            SHOCKING_EVENT = 12,
            TRAIN_BASE = 12,
            VEHICLE_FSM = 12,
            VEHICLE_GO_TO = 12,
            VEHICLE_MISSION_BASE = 12,
            VEHICLE_TEMP_ACTION = 12,
            PAUSE = 14,
            DO_NOTHING = 15,
            GET_UP = 16,
            GET_UP_AND_STAND_STILL = 17,
            FALL_OVER = 18,
            FALL_AND_GET_UP = 19,
            CRAWL = 20,
            COMPLEX_ON_FIRE = 25,
            DAMAGE_ELECTRIC = 26,
            TRIGGER_LOOK_AT = 28,
            CLEAR_LOOK_AT = 29,
            SET_CHAR_DECISION_MAKER = 30,
            SET_PED_DEFENSIVE_AREA = 31,
            USE_SEQUENCE = 32,
            MOVE_STAND_STILL = 34,
            COMPLEX_CONTROL_MOVEMENT = 35,
            MOVE_SEQUENCE = 36,
            AMBIENT_CLIPS = 38,
            MOVE_IN_AIR = 39,
            NETWORK_CLONE = 40,
            USE_CLIMB_ON_ROUTE = 41,
            USE_DROP_DOWN_ON_ROUTE = 42,
            USE_LADDER_ON_ROUTE = 43,
            SET_BLOCKING_OF_NON_TEMPORARY_EVENTS = 44,
            FORCE_MOTION_STATE = 45,
            SLOPE_SCRAMBLE = 46,
            GO_TO_AND_CLIMB_LADDER = 47,
            CLIMB_LADDER_FULLY = 48,
            RAPPEL = 49,
            VAULT = 50,
            DROP_DOWN = 51,
            AFFECT_SECONDARY_BEHAVIOUR = 52,
            AMBIENT_LOOK_AT_EVENT = 53,
            OPEN_DOOR = 54,
            SHOVE_PED = 55,
            SWAP_WEAPON = 56,
            GENERAL_SWEEP = 57,
            POLICE = 58,
            POLICE_ORDER_RESPONSE = 59,
            PURSUE_CRIMINAL = 60,
            ARREST_PED = 62,
            ARREST_PED2 = 63,
            BUSTED = 64,
            FIRE_PATROL = 65,
            HELI_ORDER_RESPONSE = 66,
            HELI_PASSENGER_RAPPEL = 67,
            AMBULANCE_PATROL = 68,
            POLICE_WANTED_RESPONSE = 69,
            SWAT = 70,
            SWAT_WANTED_RESPONSE = 72,
            SWAT_ORDER_RESPONSE = 73,
            SWAT_GO_TO_STAGING_AREA = 74,
            SWAT_FOLLOW_IN_LINE = 75,
            WITNESS = 76,
            GANG_PATROL = 77,
            ARMY = 78,
            SHOCKING_EVENT_WATCH = 80,
            SHOCKING_EVENT_GOTO = 82,
            SHOCKING_EVENT_HURRY_AWAY = 83,
            SHOCKING_EVENT_REACT_TO_AIRCRAFT = 84,
            SHOCKING_EVENT_REACT = 85,
            SHOCKING_EVENT_BACK_AWAY = 86,
            SHOCKING_POLICE_INVESTIGATE = 87,
            SHOCKING_EVENT_STOP_AND_STARE = 88,
            SHOCKING_NICE_CAR_PICTURE = 89,
            SHOCKING_EVENT_THREAT_RESPONSE = 90,
            TAKE_OFF_HELMET = 92,
            CAR_REACT_TO_VEHICLE_COLLISION = 93,
            CAR_REACT_TO_VEHICLE_COLLISION_GET_OUT = 95,
            DYING_DEAD = 97,
            WANDERING_SCENARIO = 100,
            WANDERING_IN_RADIUS_SCENARIO = 101,
            MOVE_BETWEEN_POINTS_SCENARIO = 103,
            CHAT_SCENARIO = 104,
            COWER_SCENARIO = 106,
            DEAD_BODY_SCENARIO = 107,
            SAY_AUDIO = 114,
            WAIT_FOR_STEPPING_OUT = 116,
            COUPLE_SCENARIO = 117,
            USE_SCENARIO = 118,
            USE_VEHICLE_SCENARIO = 119,
            UNALERTED = 120,
            STEAL_VEHICLE = 121,
            REACT_TO_PURSUIT = 122,
            HIT_WALL = 125,
            COWER = 126,
            CROUCH = 127,
            MELEE = 128,
            MOVE_MELEE_MOVEMENT = 129,
            MELEE_ACTION_RESULT = 130,
            MELEE_UPPERBODY_ANIMS = 131,
            MO_VE_SCRIPTED = 133,
            SCRIPTED_ANIMATION = 134,
            SYNCHRONIZED_SCENE = 135,
            COMPLEX_EVASIVE_STEP = 137,
            WALK_ROUND_CAR_WHILE_WANDERING = 138,
            COMPLEX_STUCK_IN_AIR = 140,
            WALK_ROUND_ENTITY = 141,
            MOVE_WALK_ROUND_VEHICLE = 142,
            REACT_TO_GUN_AIMED_AT = 144,
            DUCK_AND_COVER = 146,
            AGGRESSIVE_RUBBERNECK = 147,
            IN_VEHICLE_BASIC = 150,
            CAR_DRIVE_WANDER = 151,
            LEAVE_ANY_CAR = 152,
            COMPLEX_GET_OFF_BOAT = 153,
            CAR_SET_TEMP_ACTION = 155,
            BRING_VEHICLE_TO_HALT = 156,
            CAR_DRIVE = 157,
            PLAYER_DRIVE = 159,
            ENTER_VEHICLE = 160,
            ENTER_VEHICLE_ALIGN = 161,
            OPEN_VEHICLE_DOOR_FROM_OUTSIDE = 162,
            ENTER_VEHICLE_SEAT = 163,
            CLOSE_VEHICLE_DOOR_FROM_INSIDE = 164,
            IN_VEHICLE_SEAT_SHUFFLE = 165,
            EXIT_VEHICLE_SEAT = 167,
            CLOSE_VEHICLE_DOOR_FROM_OUTSIDE = 168,
            CONTROL_VEHICLE = 169,
            MOTION_IN_AUTOMOBILE = 170,
            MOTION_ON_BICYCLE = 171,
            MOTION_ON_BICYCLE_CONTROLLER = 172,
            MOTION_IN_VEHICLE = 173,
            MOTION_IN_TURRET = 174,
            REACT_TO_BEING_JACKED = 175,
            REACT_TO_BEING_ASKED_TO_LEAVE_VEHICLE = 176,
            TRY_TO_GRAB_VEHICLE_DOOR = 177,
            GET_ON_TRAIN = 178,
            GET_OFF_TRAIN = 179,
            RIDE_TRAIN = 180,
            MOUNT_THROW_PROJECTILE = 190,
            GO_TO_CAR_DOOR_AND_STAND_STILL = 195,
            MOVE_GO_TO_VEHICLE_DOOR = 196,
            SET_PED_IN_VEHICLE = 197,
            SET_PED_OUT_OF_VEHICLE = 198,
            VEHICLE_MOUNTED_WEAPON = 199,
            VEHICLE_GUN = 200,
            VEHICLE_PROJECTILE = 201,
            SMASH_CAR_WINDOW = 204,
            MOVE_GO_TO_POINT = 205,
            MOVE_ACHIEVE_HEADING = 206,
            MOVE_FACE_TARGET = 207,
            COMPLEX_GO_TO_POINT_AND_STAND_STILL_TIMED = 208,
            MOVE_GO_TO_POINT_AND_STAND_STILL = 208,
            MOVE_FOLLOW_POINT_ROUTE = 209,
            MOVE_SEEK_ENTITY_C_ENTITY_SEEK_POS_CALCULATOR_STANDARD = 210,
            MOVE_SEEK_ENTITY_C_ENTITY_SEEK_POS_CALCULATOR_LAST_NAV_MESH_INTERSECTION = 211,
            MOVE_SEEK_ENTITY_C_ENTITY_SEEK_POS_CALCULATOR_LAST_NAV_MESH_INTERSECTION2 = 212,
            MOVE_SEEK_ENTITY_C_ENTITY_SEEK_POS_CALCULATOR_XY_OFFSET_FIXED = 213,
            MOVE_SEEK_ENTITY_C_ENTITY_SEEK_POS_CALCULATOR_XY_OFFSET_FIXED2 = 214,
            EXHAUSTED_FLEE = 215,
            GROWL_AND_FLEE = 216,
            SCENARIO_FLEE = 217,
            SMART_FLEE = 218,
            FLY_AWAY = 219,
            WALK_AWAY = 220,
            WANDER = 221,
            WANDER_IN_AREA = 222,
            FOLLOW_LEADER_IN_FORMATION = 223,
            GO_TO_POINT_ANY_MEANS = 224,
            TURN_TO_FACE_ENTITY_OR_COORD = 225,
            FOLLOW_LEADER_ANY_MEANS = 226,
            FLY_TO_POINT = 228,
            FLYING_WANDER = 229,
            GO_TO_POINT_AIMING = 230,
            GO_TO_SCENARIO = 231,
            SEEK_ENTITY_AIMING = 233,
            SLIDE_TO_COORD = 234,
            SWIMMING_WANDER = 235,
            MOVE_TRACKING_ENTITY = 237,
            MOVE_FOLLOW_NAV_MESH = 238,
            MOVE_GO_TO_POINT_ON_ROUTE = 239,
            ESCAPE_BLAST = 240,
            MOVE_WANDER = 241,
            MOVE_BE_IN_FORMATION = 242,
            MOVE_CROWD_AROUND_LOCATION = 243,
            MOVE_CROSS_ROAD_AT_TRAFFIC_LIGHTS = 244,
            MOVE_WAIT_FOR_TRAFFIC = 245,
            MOVE_GO_TO_POINT_STAND_STILL_ACHIEVE_HEADING = 246,
            MOVE_GET_ONTO_MAIN_NAV_MESH = 251,
            MOVE_SLIDE_TO_COORD = 252,
            MOVE_GO_TO_POINT_RELATIVE_TO_ENTITY_AND_STAND_STILL = 253,
            HELICOPTER_STRAFE = 254,
            GET_OUT_OF_WATER = 256,
            MOVE_FOLLOW_ENTITY_OFFSET = 259,
            FOLLOW_WAYPOINT_RECORDING = 261,
            MOTION_PED = 264,
            MOTION_PED_LOW_LOD = 265,
            HUMAN_LOCOMOTION = 268,
            MOTION_BASIC_LOCOMOTION_LOW_LOD = 269,
            MOTION_STRAFING = 270,
            MOTION_TENNIS = 271,
            MOTION_AIMING = 272,
            BIRD_LOCOMOTION = 273,
            FLIGHTLESS_BIRD_LOCOMOTION = 274,
            FISH_LOCOMOTION = 278,
            QUAD_LOCOMOTION = 279,
            MOTION_DIVING = 280,
            MOTION_SWIMMING = 281,
            MOTION_PARACHUTING = 282,
            MOTION_DRUNK = 283,
            REPOSITION_MOVE = 284,
            MOTION_AIMING_TRANSITION = 285,
            THROW_PROJECTILE = 286,
            COVER = 287,
            MOTION_IN_COVER = 288,
            AIM_AND_THROW_PROJECTILE = 289,
            GUN = 290,
            AIM_FROM_GROUND = 291,
            AIM_GUN_VEHICLE_DRIVE_BY = 295,
            AIM_GUN_SCRIPTED = 296,
            RELOAD_GUN = 298,
            WEAPON_BLOCKED = 299,
            ENTER_COVER = 300,
            EXIT_COVER = 301,
            AIM_GUN_FROM_COVER_INTRO = 302,
            AIM_GUN_FROM_COVER_OUTRO = 303,
            AIM_GUN_BLIND_FIRE = 304,
            COMBAT_CLOSEST_TARGET_IN_AREA = 307,
            COMBAT_ADDITIONAL_TASK = 308,
            IN_COVER = 309,
            AIM_SWEEP = 313,
            SHARK_CIRCLE = 319,
            SHARK_ATTACK = 320,
            AGITATED = 321,
            AGITATED_ACTION = 322,
            CONFRONT = 323,
            INTIMIDATE = 324,
            SHOVE = 325,
            SHOVED = 326,
            CROUCH_TOGGLE = 328,
            REVIVE = 329,
            PARACHUTE = 335,
            PARACHUTE_OBJECT = 336,
            TAKE_OFF_PED_VARIATION = 337,
            COMBAT_SEEK_COVER = 340,
            COMBAT_FLANK = 342,
            COMBAT = 343,
            COMBAT_MOUNTED = 344,
            MOVE_CIRCLE = 345,
            MOVE_COMBAT_MOUNTED = 346,
            SEARCH = 347,
            SEARCH_ON_FOOT = 348,
            SEARCH_IN_AUTOMOBILE = 349,
            SEARCH_IN_BOAT = 350,
            SEARCH_IN_HELI = 351,
            THREAT_RESPONSE = 352,
            INVESTIGATE = 353,
            STAND_GUARD_FSM = 354,
            PATROL = 355,
            SHOOT_AT_TARGET = 356,
            SET_AND_GUARD_AREA = 357,
            STAND_GUARD = 358,
            SEPARATE = 359,
            STAY_IN_COVER = 360,
            VEHICLE_COMBAT = 361,
            VEHICLE_PERSUIT = 362,
            VEHICLE_CHASE = 363,
            DRAGGING_TO_SAFETY = 364,
            DRAGGED_TO_SAFETY = 365,
            VARIED_AIM_POSE = 366,
            MOVE_WITHIN_ATTACK_WINDOW = 367,
            MOVE_WITHIN_DEFENSIVE_AREA = 368,
            SHOOT_OUT_TIRE = 369,
            SHELL_SHOCKED = 370,
            BOAT_CHASE = 371,
            BOAT_COMBAT = 372,
            BOAT_STRAFE = 373,
            HELI_CHASE = 374,
            HELI_COMBAT = 375,
            SUBMARINE_COMBAT = 376,
            SUBMARINE_CHASE = 377,
            PLANE_CHASE = 378,
            TARGET_UNREACHABLE = 379,
            TARGET_UNREACHABLE_IN_INTERIOR = 380,
            TARGET_UNREACHABLE_IN_EXTERIOR = 381,
            STEALTH_KILL = 382,
            WRITHE = 383,
            ADVANCE = 384,
            CHARGE = 385,
            MOVE_TO_TACTICAL_POINT = 386,
            TO_HURT_TRANSIT = 387,
            ANIMATED_HIT_BY_EXPLOSION = 388,
            NM_RELAX = 389,
            NM_POSE = 391,
            NM_BRACE = 392,
            NM_BUOYANCY = 393,
            NM_INJURED_ON_GROUND = 394,
            NM_SHOT = 395,
            NM_HIGH_FALL = 396,
            NM_BALANCE = 397,
            NM_ELECTROCUTE = 398,
            NM_PROTOTYPE = 399,
            NM_EXPLOSION = 400,
            NM_ON_FIRE = 401,
            NM_SCRIPT_CONTROL = 402,
            NM_JUMP_ROLL_FROM_ROAD_VEHICLE = 403,
            NM_FLINCH = 404,
            NM_SIT = 405,
            NM_FALL_DOWN = 406,
            BLEND_FROM_NM = 407,
            NM_CONTROL = 408,
            NM_DANGLE = 409,
            NM_GENERIC_ATTACH = 412,
            NM_DRAGGING_TO_SAFETY = 414,
            NM_THROUGH_WINDSCREEN = 415,
            NM_RIVER_RAPIDS = 416,
            NM_SIMPLE = 417,
            RAGE_RAGDOLL = 418,
            JUMP_VAULT = 421,
            JUMP = 422,
            FALL = 423,
            REACT_AIM_WEAPON = 425,
            CHAT = 426,
            MOBILE_PHONE = 427,
            REACT_TO_DEAD_PED = 428,
            SEARCH_FOR_UNKNOWN_THREAT = 430,
            BOMB = 432,
            DETONATOR = 433,
            ANIMATED_ATTACH = 435,
            CUT_SCENE = 441,
            REACT_TO_EXPLOSION = 442,
            REACT_TO_IMMINENT_EXPLOSION = 443,
            DIVE_TO_GROUND = 444,
            REACT_AND_FLEE = 445,
            SIDESTEP = 446,
            CALL_POLICE = 447,
            REACT_IN_DIRECTION = 448,
            REACT_TO_BUDDY_SHOT = 449,
            VEHICLE_GO_TO_AUTOMOBILE_NEW = 454,
            VEHICLE_GO_TO_PLANE = 455,
            VEHICLE_GO_TO_HELICOPTER = 456,
            VEHICLE_GO_TO_SUBMARINE = 457,
            VEHICLE_GO_TO_BOAT = 458,
            VEHICLE_GO_TO_POINT_AUTOMOBILE = 459,
            VEHICLE_GO_TO_POINT_WITH_AVOIDANCE_AUTOMOBILE = 460,
            VEHICLE_PURSUE = 461,
            VEHICLE_RAM = 462,
            VEHICLE_SPIN_OUT = 463,
            VEHICLE_APPROACH = 464,
            VEHICLE_THREE_POINT_TURN = 465,
            VEHICLE_DEAD_DRIVER = 466,
            VEHICLE_CRUISE_NEW = 467,
            VEHICLE_CRUISE_BOAT = 468,
            VEHICLE_STOP = 469,
            VEHICLE_PULL_OVER = 470,
            VEHICLE_PASSENGER_EXIT = 471,
            VEHICLE_FLEE = 472,
            VEHICLE_FLEE_AIRBORNE = 473,
            VEHICLE_FLEE_BOAT = 474,
            VEHICLE_FOLLOW_RECORDING = 475,
            VEHICLE_FOLLOW = 476,
            VEHICLE_BLOCK = 477,
            VEHICLE_BLOCK_CRUISE_IN_FRONT = 478,
            VEHICLE_BLOCK_BRAKE_IN_FRONT = 479,
            VEHICLE_BLOCK_BACK_AND_FORTH = 478,
            VEHICLE_CRASH = 481,
            VEHICLE_LAND = 482,
            VEHICLE_LAND_PLANE = 483,
            VEHICLE_HOVER = 484,
            VEHICLE_ATTACK = 485,
            VEHICLE_ATTACK_TANK = 486,
            VEHICLE_CIRCLE = 487,
            VEHICLE_POLICE_BEHAVIOUR = 488,
            VEHICLE_POLICE_BEHAVIOUR_HELICOPTER = 489,
            VEHICLE_POLICE_BEHAVIOUR_BOAT = 490,
            VEHICLE_ESCORT = 491,
            VEHICLE_HELI_PROTECT = 492,
            VEHICLE_PLAYER_DRIVE_AUTOMOBILE = 494,
            VEHICLE_PLAYER_DRIVE_BIKE = 495,
            VEHICLE_PLAYER_DRIVE_BOAT = 496,
            VEHICLE_PLAYER_DRIVE_SUBMARINE = 497,
            VEHICLE_PLAYER_DRIVE_SUBMARINE_CAR = 498,
            VEHICLE_PLAYER_DRIVE_AMPHIBIOUS_AUTOMOBILE = 499,
            VEHICLE_PLAYER_DRIVE_PLANE = 500,
            VEHICLE_PLAYER_DRIVE_HELI = 501,
            VEHICLE_PLAYER_DRIVE_AUTOGYRO = 502,
            VEHICLE_PLAYER_DRIVE_DIGGER_ARM = 503,
            VEHICLE_PLAYER_DRIVE_TRAIN = 504,
            VEHICLE_PLANE_CHASE = 505,
            VEHICLE_NO_DRIVER = 506,
            VEHICLE_ANIMATION = 507,
            VEHICLE_CONVERTIBLE_ROOF = 508,
            VEHICLE_PARK_NEW = 509,
            VEHICLE_FOLLOW_WAYPOINT_RECORDING = 510,
            VEHICLE_GO_TO_NAVMESH = 511,
            VEHICLE_REACT_TO_COP_SIREN = 512,
            VEHICLE_GOTO_LONG_RANGE = 513,
            VEHICLE_WAIT = 514,
            VEHICLE_REVERSE = 515,
            VEHICLE_BRAKE = 516,
            VEHICLE_HAND_BRAKE = 517,
            VEHICLE_TURN = 518,
            VEHICLE_GO_FORWARD = 519,
            VEHICLE_SWERVE = 520,
            VEHICLE_FLY_DIRECTION = 521,
            VEHICLE_HEADON_COLLISION = 522,
            VEHICLE_BOOST_USE_STEERING_ANGLE = 523,
            VEHICLE_SHOT_TIRE = 524,
            VEHICLE_BURNOUT = 525,
            VEHICLE_REV_ENGINE = 526,
            VEHICLE_SURFACE_IN_SUBMARINE = 527,
            VEHICLE_PULL_ALONGSIDE = 528,
            VEHICLE_TRANSFORM_TO_SUBMARINE = 529,
            ANIMATED_FALLBACK = 530
        }
    }
}

declare abstract class Timer {
    public interval: number;
    public callback: Function;
    public lastTick: number;
    public once?: boolean;
    public location: import("@altv/shared").SourceLocation;

    public get type(): import("@altv/shared").Enums.TimerType;
    public get id(): number;

    public destroy(): void;
}
