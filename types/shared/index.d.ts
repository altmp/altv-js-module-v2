/**
 * @module @altv/shared
 */

declare module "@altv/shared" {
    export const isDebug: boolean;
    export const version: string;
    export const branch: string;

    export const isClient: boolean;
    export const isServer: boolean;

    export function log(...args: any[]): void;
    export function logWarning(...args: any[]): void;
    export function logError(...args: any[]): void;

    export function sha256(data: string): string;
    export function hash(data: string): number;

    export const meta: Record<string, any>;

    export namespace Timers {
        class Timer {
            destroy(): void;
        }

        export class Interval extends Timer {
            constructor(callback: () => void, interval: number);
        }

        export class Timeout extends Timer {
            constructor(callback: () => void, timeout: number);
        }

        export class EveryTick extends Timer {
            constructor(callback: () => void);
        }

        export class NextTick extends Timer {
            constructor(callback: () => void);
        }

        export function setInterval(callback: () => void, interval: number): Interval;
        export function setTimeout(callback: () => void, timeout: number): Timeout;
        export function everyTick(callback: () => void): EveryTick;
        export function nextTick(callback: () => void): NextTick;

        export function setWarningThreshold(treshold: number): void;
        export function setSourceLocationFrameSkipCount(count: number): void;

        export const all: Timer[];
    }

    export namespace Utils {
        export function inspect(object: any, options?: any): string;

        export function wait(ms: number): Promise<void>;
        export function waitForNextTick(): Promise<void>;
        export function waitFor(callback: () => boolean, timeout: number): Promise<void>;

        export function getCurrentSourceLocation(frameSkipCount: number): number;

        export class AssertionError extends Error {}
        export function assert(condition: any, message?: string): asserts condition;
    }

    export namespace Factory {
        export function setPlayerFactory<T extends Player>(factory: new () => T): void;
        export function getPlayerFactory(): new () => unknown;

        export function setVehicleFactory<T extends Vehicle>(factory: new () => T): void;
        export function getVehicleFactory(): new () => unknown;

        export function setPedFactory<T extends Ped>(factory: new () => T): void;
        export function getPedFactory(): new () => unknown;

        export function setBlipFactory<T extends Blip>(factory: new () => T): void;
        export function getBlipFactory(): new () => unknown;
    }

    export namespace Enums {
        // See https://github.com/altmp/cpp-sdk/blob/master/objects/IBaseObject.h#L14
        export const enum BaseObjectType {
            PLAYER,
            VEHICLE,
            PED,
            NETWORK_OBJECT,
            BLIP,
            WEBVIEW,
            VOICE_CHANNEL,
            COLSHAPE,
            CHECKPOINT,
            WEBSOCKET_CLIENT,
            HTTP_CLIENT,
            AUDIO,
            RML_ELEMENT,
            RML_DOCUMENT,
            LOCAL_PLAYER,
            OBJECT,
            VIRTUAL_ENTITY,
            VIRTUAL_ENTITY_GROUP,
            MARKER,
            TEXT_LABEL,
            PICKUP,
            SIZE
        }
        export const enum Permission {
            NONE,
            SCREEN_CAPTURE,
            WEBRTC,
            CLIPBOARD_ACCESS,
            EXTENDED_VOICE_API,
            All
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
        export const enum ColShapeType {
            SPHERE,
            CYLINDER,
            CIRCLE,
            CUBOID,
            RECT,
            CHECKPOINT_CYLINDER,
            POLYGON
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
            PLAYER_CONNECT,
            PLAYER_CONNECT_DENIED,
            PLAYER_DISCONNECT,
            PLAYER_DAMAGE,
            PLAYER_DEATH,
            PLAYER_ENTER_VEHICLE,
            PLAYER_ENTERING_VEHICLE,
            PLAYER_LEAVE_VEHICLE,
            PLAYER_CHANGE_VEHICLE_SEAT,
            PLAYER_WEAPON_CHANGE,
            PLAYER_REQUEST_CONTROL,
            PLAYER_CHANGE_INTERIOR_EVENT,
            PLAYER_DIMENSION_CHANGE,
            PLAYER_CHANGE_ANIMATION_EVENT,
            COLSHAPE_EVENT,
            WEAPON_DAMAGE_EVENT,
            EXPLOSION_EVENT,
            FIRE_EVENT,
            START_PROJECTILE_EVENT,
            SERVER_STARTED,
            CONNECTION_QUEUE_ADD,
            CONNECTION_QUEUE_REMOVE,
            VEHICLE_DESTROY,
            VEHICLE_ATTACH,
            VEHICLE_DETACH,
            VEHICLE_DAMAGE,
            VEHICLE_SIREN,
            CONSOLE_COMMAND_EVENT,
            CREATE_BASE_OBJECT_EVENT,
            REMOVE_BASE_OBJECT_EVENT,
            NETOWNER_CHANGE,
            LOCAL_SYNCED_META_CHANGE,
            SYNCED_META_CHANGE,
            STREAM_SYNCED_META_CHANGE,
            GLOBAL_META_CHANGE,
            GLOBAL_SYNCED_META_CHANGE,
            RESOURCE_START,
            RESOURCE_STOP,
            RESOURCE_ERROR,
            SERVER_SCRIPT_EVENT,
            CLIENT_SCRIPT_EVENT
        }
        export const enum CustomEventType {
            ENTITY_ENTER_COLSHAPE,
            ENTITY_LEAVE_COLSHAPE,
            ENTITY_ENTER_CHECKPOINT,
            ENTITY_LEAVE_CHECKPOINT,
            ERROR
        }
    }

    export namespace Events {
        export interface EventContext {
            cancel(): void;
            readonly isCancelled: boolean;
        }
        export interface Event<Context extends EventContext> {
            (callback: (context: Context) => void): void;

            remove(callback: (context: Context) => void): void;
            readonly listeners: ReadonlyArray<(context: Context) => void>;
        }
        export interface ScriptEvent<Context extends ScriptEventContext> {
            (name: string, callback: (context: Context) => void): void;

            remove(callback: (name: string, context: Context) => void): void;
            readonly listeners: Record<string, ReadonlyArray<(name: string, context: Context) => void>>;
        }

        interface ScriptEventContext extends EventContext {
            readonly eventName: string;
            readonly args: any[];
        }
        interface ServerEventContext extends ScriptEventContext {}
        interface ConsoleCommandEventContext extends EventContext {
            readonly command: string;
            readonly args: string[];
        }
        interface ErrorEventContext extends EventContext {
            readonly error: string;
            readonly stack: string;
        }
        interface ResourceEventContext extends EventContext {
            readonly resource: Resource;
        }
        interface PlayerAnimationChangeEventContext extends EventContext {
            readonly player: Player;
            readonly oldAnimDict: number;
            readonly oldAnimName: number;
            readonly newAnimDict: number;
            readonly newAnimName: number;
        }
        interface LocalMetaChangeEventContext extends EventContext {
            readonly player: Player;
            readonly key: string;
            readonly oldValue: any;
            readonly newValue: any;
        }
        interface SyncedMetaChangeEventContext extends EventContext {
            readonly entity: Entity;
            readonly key: string;
            readonly oldValue: any;
            readonly newValue: any;
        }
        interface StreamSyncedMetaChangeEventContext extends EventContext {
            readonly entity: Entity;
            readonly key: string;
            readonly oldValue: any;
            readonly newValue: any;
        }
        interface GlobalMetaChangeEventContext extends EventContext {
            readonly key: string;
            readonly oldValue: any;
            readonly newValue: any;
        }
        interface SyncedGlobalMetaChangeEventContext extends EventContext {
            readonly key: string;
            readonly oldValue: any;
            readonly newValue: any;
        }
        interface BaseObjectCreateEventContext extends EventContext {
            readonly object: BaseObject;
        }
        interface BaseObjectRemoveEventContext extends EventContext {
            readonly object: BaseObject;
        }
        interface NetOwnerChangeEventContext extends EventContext {
            readonly entity: Entity;
            readonly oldOwner: Player;
            readonly newOwner: Player;
        }

        export const onConsoleCommand: Event<ConsoleCommandEventContext>;

        export const onError: Event<ErrorEventContext>;

        export const onResourceStart: Event<ResourceEventContext>;
        export const onResourceStop: Event<ResourceEventContext>;
        export const onResourceError: Event<ResourceEventContext>;

        export const onPlayerAnimationChange: Event<PlayerAnimationChangeEventContext>;

        export const onLocalMetaChange: Event<LocalMetaChangeEventContext>;
        export const onSyncedMetaChange: Event<SyncedMetaChangeEventContext>;
        export const onStreamSyncedMetaChange: Event<StreamSyncedMetaChangeEventContext>;
        export const onGlobalMetaChange: Event<GlobalMetaChangeEventContext>;
        export const onSyncedGlobalMetaChange: Event<SyncedGlobalMetaChangeEventContext>;

        export const onBaseObjectCreate: Event<BaseObjectCreateEventContext>;
        export const onBaseObjectRemove: Event<BaseObjectRemoveEventContext>;

        export const onNetOwnerChange: Event<NetOwnerChangeEventContext>;

        export const on: ScriptEvent<ScriptEventContext>;

        export function emit(eventName: string, ...args: any[]): void;

        export function setWarningThreshold(treshold: number): void;
        export function setSourceLocationFrameSkipCount(count: number): void;
    }

    export namespace PointBlip {}
    export namespace AreaBlip {}
    export namespace RadiusBlip {}

    class Vector<T> {
        add(other: T): T;
        sub(other: T): T;
        mul(other: T): T;
        div(other: T): T;

        dot(other: T): number;

        toArray(): number[];
        toFixed(digits?: number): T;

        get length(): number;
        get lengthSquared(): number;
        get negative(): T;
        get inverse(): T;
        get normalized(): T;

        distanceTo(other: T): number;
        distanceToSquared(other: T): number;
        angleTo(other: T): number;
        angleToDegrees(other: T): number;

        toDegrees(): T;
        toRadians(): T;

        isInRange(range: number, other: T): boolean;
        lerp(ratio: number, other: T): T;
    }

    export class Vector3 extends Vector<Vector3> {
        constructor(x: number, y: number, z: number);
        constructor(values: [number, number, number]);
        constructor(values: { x: number; y: number; z: number });

        get x(): number;
        get y(): number;
        get z(): number;

        static get zero(): Vector3;
        static get one(): Vector3;
        static get up(): Vector3;
        static get down(): Vector3;
        static get left(): Vector3;
        static get right(): Vector3;
        static get forward(): Vector3;
        static get back(): Vector3;
        static get negativeInfinity(): Vector3;
        static get positiveInfinity(): Vector3;
    }

    export class Vector2 extends Vector<Vector2> {
        constructor(x: number, y: number);
        constructor(values: [number, number]);
        constructor(values: { x: number; y: number });

        get x(): number;
        get y(): number;

        static get zero(): Vector2;
        static get one(): Vector2;
        static get up(): Vector2;
        static get down(): Vector2;
        static get left(): Vector2;
        static get right(): Vector2;
        static get negativeInfinity(): Vector2;
        static get positiveInfinity(): Vector2;
    }

    export class RGBA {
        constructor(r: number, g: number, b: number, a?: number);
        constructor(values: [number, number, number, number]);
        constructor(values: { r: number; g: number; b: number; a?: number });

        get r(): number;
        get g(): number;
        get b(): number;
        get a(): number;

        toArray(): [number, number, number, number];
        toInt(): number;

        static get zero(): RGBA;
        static fromInt(value: number): RGBA;
    }

    export class Quaternion {
        constructor(x: number, y: number, z: number, w: number);
        constructor(values: [number, number, number, number]);
        constructor(values: { x: number; y: number; z: number; w: number });

        get x(): number;
        get y(): number;
        get z(): number;
        get w(): number;
        get length(): number;
        get lengthSquared(): number;
        get conjugate(): Quaternion;
        get inverse(): Quaternion;
        get normalized(): Quaternion;
        get pitch(): number;
        get yaw(): number;
        get roll(): number;
        get eulerAngles(): Vector3;
        get axis(): Vector3;
        get angle(): number;
        get matrix(): ReadonlyArray<number>;
        get forward(): Vector3;
        get right(): Vector3;
        get up(): Vector3;
        get left(): Vector3;
        get back(): Vector3;
        get down(): Vector3;

        static fromEuler(x: number, y: number, z: number): Quaternion;
        static fromAxisAngle(axis: Vector3, angel: number): Quaternion;
        static fromMatrix(matrix: Array<number>): Quaternion;
        static fromArray(array: Array<number>): Quaternion;
    }

    export class Resource {
        get type(): string;
        get path(): string;
        get name(): string;
        get main(): string;
        get exports(): Record<string, any>;
        get dependencies(): ReadonlyArray<Resource>;
        get dependents(): ReadonlyArray<Resource>;
        get isStarted(): boolean;

        static get(name: string): Resource | null;
        static exists(name: string): boolean;
        static start(name: string): boolean;
        static stop(name: string): boolean;
        static restart(name: string): boolean;

        static get current(): Resource;
        static get all(): ReadonlyArray<Resource>;
    }

    export interface BaseObject {
        get type(): Enums.BaseObjectType;
        get valid(): boolean;

        get meta(): Record<string, any>;

        destroy(): void;
    }

    export class BaseObject {
        static getById(type: Enums.BaseObjectType, id: number): BaseObject | null;
    }

    export interface WorldObject extends BaseObject {
        get pos(): Vector3;
    }

    export class WorldObject {}

    export interface Entity extends WorldObject {
        get id(): number;

        get model(): number;
        get netOwner(): Player | null;
        get rot(): Vector3;
        get visible(): boolean;

        get syncedMeta(): Record<string, any>;
        get streamSyncedMeta(): Record<string, any>;
    }

    export class Entity {
        static get all(): ReadonlyArray<Entity>;
    }

    export interface Ped extends Entity {
        get health(): number;
        get maxHealth(): number;
        get armour(): number;
        get currentWeapon(): number;
    }

    export class Ped {
        static get all(): ReadonlyArray<Ped>;
    }

    export interface Player extends Entity {
        get name(): string;
        get health(): number;
        get maxHealth(): number;
        get currentWeaponComponents(): ReadonlyArray<number>;
        get currentWeaponTintIndex(): number;
        get currentWeapon(): number;
        get isDead(): boolean;
        get isJumping(): boolean;
        get isInRagdoll(): boolean;
        get isAiming(): boolean;
        get isShooting(): boolean;
        get isReloading(): boolean;
        get isEnteringVehicle(): boolean;
        get isLeavingVehicle(): boolean;
        get isOnLadder(): boolean;
        get isInMelee(): boolean;
        get isInCover(): boolean;
        get armour(): number;
        get maxArmour(): number;
        get moveSpeed(): number;
        get aimPos(): Vector3;
        get headRotation(): Vector3;
        get isInVehicle(): boolean;
        get vehicle(): Vehicle | undefined;
        get seat(): number;
        get entityAimingAt(): Entity | undefined;
        get entityAimOffset(): Vector3;
        get isFlashlightActive(): boolean;
        get isSuperJumpEnabled(): boolean;
        get isCrouching(): boolean;
        get isStealthy(): boolean;
        get currentAnimationDict(): string;
        get currentAnimationName(): string;
        get isSpawned(): boolean;
        get forwardSpeed(): number;
        get strafeSpeed(): number;

        getWeaponTintIndex(weapon: number | string): number;
        hasWeaponComponent(weapon: number | string, component: number | string): boolean;
    }

    export class Player {
        static get all(): ReadonlyArray<Player>;
    }

    export interface Vehicle extends Entity {
        get neon(): Record<string, boolean>;
        get driver(): Player;
        get isDestroyed(): boolean;
        get modKitsCount(): number;
        get modKit(): number;
        get isPrimaryColorRGB(): boolean;
        get primaryColor(): number;
        get customPrimaryColor(): RGBA;
        get isSecondaryColorRGB(): boolean;
        get secondaryColor(): number;
        get customSecondaryColor(): RGBA;
        get pearlColor(): number;
        get wheelColor(): number;
        get interiorColor(): number;
        get dashboardColor(): number;
        get isTireSmokeColorCustom(): boolean;
        get tireSmokeColor(): RGBA;
        get wheelType(): number;
        get wheelVariation(): number;
        get customTires(): boolean;
        get specialDarkness(): number;
        get numberplateIndex(): number;
        get numberplateText(): string;
        get windowTint(): number;
        get dirtLevel(): number;
        get isNeonActive(): boolean;
        get neonColor(): RGBA;
        get livery(): number;
        get roofLivery(): number;
        get appearanceDataBase64(): string;
        get isEngineOn(): boolean;
        get isHandbrakeActive(): boolean;
        get headlightColor(): number;
        get radioStationIndex(): number;
        get isSirenActive(): boolean;
        get lockState(): Enums.VehicleLockState;
        get isDaylightOn(): boolean;
        get isNightlightOn(): boolean;
        get roofState(): number;
        get isFlamethrowerActive(): boolean;
        get lightsMultiplier(): number;
        get gameStateBase64(): string;
        get engineHealth(): number;
        get petrolTankHealth(): number;
        get wheelsCount(): number;
        get repairsCount(): number;
        get bodyHealth(): number;
        get bodyAdditionalHealth(): number;
        get hasArmoredWindows(): boolean;
        get damageDataBase64(): string;
        get isManualEngineControl(): boolean;
        get scriptDataBase64(): string;
        get velocity(): Vector3;

        getMod(category: number): number;
        getModsCount(category: number): number;
        isExtraOn(extraId: number): boolean;
        getDoorState(doorId: number): number;
        isWindowOpened(windowId: number): boolean;
        isWheelBurst(wheelId: number): boolean;
        doesWheelHasTire(wheelId: number): boolean;
        isWheelDetached(wheelId: number): boolean;
        isWheelOnFire(wheelId: number): boolean;
        getWheelHealth(wheelId: number): number;
        getPartDamageLevel(partId: number): number;
        getPartBulletHoles(partId: number): number;
        isLightDamaged(lightId: number): boolean;
        isWindowDamaged(windowId: number): boolean;
        isSpecialLightDamaged(lightId: number): boolean;
        getArmoredWindowHealth(windowId: number): number;
        getArmoredWindowShootCount(windowId: number): number;
        getBumperDamageLevel(bumperId: number): number;
        toggleExtra(extraId: number, state: boolean): void;
    }

    export class Vehicle {
        static get all(): ReadonlyArray<Player>;
    }

    export interface NetworkObject extends Entity {
        get alpha(): number;
        get textureVariation(): number;
        get lodDistance(): number;
    }

    export class NetworkObject {
        static get all(): ReadonlyArray<NetworkObject>;
    }

    export interface Blip extends BaseObject {
        get id(): number;

        get isGlobal(): boolean;
        get target(): Player;
        get isAttached(): boolean;
        get attachedTo(): Entity;
        get blipType(): Enums.BlipType;
        scale: Vector2;
        display: number;
        sprite: number;
        color: number;
        secondaryColor: RGBA;
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

        attachTo(entity: Entity): void;
        fade(opacity: number, duration: number): void;
    }

    export class Blip {
        static get all(): ReadonlyArray<Blip>;
    }

    export interface ColShape extends WorldObject {}

    export class ColShape {}

    export interface Checkpoint extends ColShape {}

    export class Checkpoint {}

    export interface VirtualEntityGroup extends BaseObject {
        get id(): number;
        get streamingRangeLimit(): number;
    }

    export class VirtualEntityGroup extends BaseObject {
        static get all(): ReadonlyArray<VirtualEntityGroup>;
    }

    export interface VirtualEntity extends WorldObject {
        get id(): number;
        get group(): VirtualEntityGroup;
        get streamingDistance(): number;

        get streamSyncedMeta(): Record<string, any>;
    }

    export class VirtualEntity extends WorldObject {
        static get all(): ReadonlyArray<VirtualEntity>;
    }

    export namespace Appearance {
        interface Clothing {
            drawable: number;
            texture: number;
            palette: number;
        }

        interface DlcClothing extends Clothing {
            dlc: number;
        }

        interface Prop {
            drawable: number;
            palette: number;
        }

        interface DlcProp extends Prop {
            dlc: number;
        }

        interface HeadblendData {
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

        interface HeadOverlay {
            index: number;
            opacity: number;
            colorType: number;
            colorIndex: number;
            secondColorIndex: number;
        }
    }

    export interface WeaponInfo {
        get hash(): number;
        get tintIndex(): number;
        get components(): ReadonlyArray<number>;
    }
}
