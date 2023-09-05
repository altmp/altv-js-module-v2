/**
 * @module @altv/shared
 */

declare module "@altv/shared" {
    export abstract class BaseObject {
        readonly id: number;
        readonly type: number;

        readonly valid: boolean;
        destroy(): void;

        meta: Record<string, unknown>;

        static getByID(id: number): BaseObject | null;
    }

    export abstract class Blip {
        readonly global: boolean;
        readonly isAttached: boolean;
        readonly attachedTo?: Entity;
        blipType: number; // TODO (xLuxy): BlipType enum
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
        nextPos: IVector3;
        readonly streamingDistance: number;
        visible: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: IVector3): boolean;
    }

    // NOTE (xLuxy): only exists on server and client namespace
    //               this is just here for extending - see Checkpoint
    export abstract class ColShape {}

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

        // TODO (xLuxy): what's the second fields type?
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
    }

    export abstract class VirtualEntityGroup extends BaseObject {
        readonly maxEntitiesInStream: number;
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

    // Vehicle interfaces
    export interface NeonState {
        readonly left: boolean;
        readonly right: boolean;
        readonly front: boolean;
        readonly back: boolean;
    }
}

declare const enum BaseObjectType {
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
