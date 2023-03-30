/**
 * @module @altv/shared
 */

declare module "@altv/shared" {
    export const isDebug: boolean;
    export const version: string;
    export const branch: string;

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
    }

    export namespace Utils {
        export function inspect(object: any, options?: any): string;

        export function wait(ms: number): Promise<void>;
        export function waitForNextTick(): Promise<void>;
        export function waitFor(callback: () => boolean): Promise<void>;
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
        // todo: add missing enums
    }

    export namespace Events {
        export interface EventContext {
            cancel(): void;
            readonly isCancelled: boolean;
        }
        export interface Event<Context extends EventContext> {
            (callback: (context: Context) => void): void;

            remove(callback: Callback): void;
            readonly listeners: ReadonlyArray<(context: Context) => void>;
        };

        interface ClientScriptEventContext extends EventContext {
            readonly eventName: string;
            readonly args: any[];
            readonly player: Player | undefined;
        }
        interface ServerEventContext extends EventContext {
            readonly eventName: string;
            readonly args: any[];
        }
        interface ConsoleCommandEventContext extends EventContext {
            readonly name: string;
            readonly args: string[];
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

        export const onClientScriptEvent: Event<ClientScriptEventContext>;
        export const onServerScriptEvent: Event<ServerEventContext>;

        export const onConsoleCommand: Event<ConsoleCommandEventContext>;

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

        export function emit(name: string, ...args: any[]): void;
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
        constructor(values: { x: number, y: number, z: number });

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
        constructor(values: { x: number, y: number });

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
        constructor(values: { r: number, g: number, b: number, a?: number });

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
        constructor(values: { x: number, y: number, z: number, w: number });

        // todo: add missing api

        get x(): number;
        get y(): number;
        get z(): number;
        get w(): number;
    }

    export class BaseObject {
        get type(): Enums.BaseObjectType;
        get valid(): boolean;

        get meta(): Record<string, any>;

        destroy(): void;
    }

    export class WorldObject extends BaseObject {
        get pos(): Vector3;
    }

    export class Entity extends WorldObject {
        get id(): number;
        get model(): number;
        get netOwner(): Player | null;
        get rot(): Vector3;
        get visible(): boolean;

        get syncedMeta(): Record<string, any>;
        get streamSyncedMeta(): Record<string, any>;
    }

    export class Resource {
        get type(): string;
        get name(): string;
        get path(): string;
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

    export class Player extends Entity {
        get name(): string;
        get health(): number;
        get maxHealth(): number;
        get currentWeaponComponents(): ReadonlyArray<number>;
        get currentWeaponTintIndex(): number;
        get currentWeapon(): number;
        get isDead(): boolean;
        get isJumping(): boolean;
        get isAiming(): boolean;
        get isShooting(): boolean;
        get isReloading(): boolean;
        get armour(): number;
        get maxArmour(): number;
        get moveSpeed(): number;
        get aimPos(): Vector3;
        get headRotation(): Vector3;
        get isInVehicle(): boolean;
        get vehicle(): Vehicle | null;
        get seat(): number;
        get entityAimingAt(): Entity | null;
        get entityAimOffset(): Vector3;
        get isFlashlightActive(): boolean;
        get isSuperJumpEnabled(): boolean;
        get isCrouching(): boolean;
        get isStealthy(): boolean;
        get currentAnimationDict(): number;
        get currentAnimationName(): number;
        get isSpawned(): boolean;
        get forwardSpeed(): number;
        get strafeSpeed(): number;

        getWeaponTintIndex(weapon: number | string): number;
        hasWeaponComponent(weapon: number | string, component: number | string): boolean;
    }

    export class Vehicle extends Entity {
        // todo: add missing api
    }

    export class Blip extends WorldObject {
        get id(): number;
        get isGlobal(): boolean;
        get target(): Entity | null;
        get isAttached(): boolean;
        get attachedTo(): Entity | null;
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

    export class NetworkObject extends Entity {
        get alpha(): number;
        get textureVariation(): number;
        get lodDistance(): number;
    }

    export class Ped extends Entity {
        get health(): number;
        get maxHealth(): number;
        get armour(): number;
        get currentWeapon(): number;
    }
}
