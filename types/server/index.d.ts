/**
 * @module @altv/server
 */
declare module "@altv/server" {
    import * as shared from "@altv/shared";

    export const rootDir: string;
    export const netTime: number;

    export const syncedMeta: Record<string, any>;
    export const serverConfig: Record<string, any>;

    export function setServerPassword(password: string): void;
    export function hashServerPassword(password: string): number;
    export function stopServer(): void;
    export function toggleWorldProfiler(enabled: boolean): void;

    export function getEntitiesInDimension(dimension: number, entityTypes: number): ReadonlyArray<Entity>;
    export function getEntitiesInRange(pos: shared.Vector3, range: number, dimension: number, entityTypes: number): ReadonlyArray<Entity>;
    export function getClosestEntities(pos: shared.Vector3, range: number, dimension: number, maxCount: number, entityTypes: number): ReadonlyArray<Entity>;

    export namespace Events {
        // todo: add server events

        export function emitPlayers(players: Player[], eventName: string, ...args: any[]): void;
        export function emitPlayersUnreliable(players: Player[], eventName: string, ...args: any[]): void;
        export function emitAllPlayers(eventName: string, ...args: any[]): void;
        export function emitAllPlayersUnreliable(eventName: string, ...args: any[]): void;
    }

    export interface BoneInfo {
        get id(): number;
        get index(): number;
        get name(): string;
    }

    export interface PedModelInfo {
        get hash(): number;
        get name(): string;
        get type(): number;
        get dlcName(): string;
        get defaultUnarmedWeapon(): string;
        get movementClipSet(): string;
        get bones(): ReadonlyArray<BoneInfo>;

        static get(model: string | number): PedModelInfo;
    }

    export interface VehicleModelInfo {
        get title(): string;
        get modelType(): shared.Enums.VehicleModelType;
        get wheelsCount(): number;
        get hasArmoredWindows(): boolean;
        get primaryColor(): number;
        get secondaryColor(): number;
        get pearlColor(): number;
        get wheelsColor(): number;
        get interiorColor(): number;
        get dashboardColor(): number;
        get modkits(): ReadonlyArray<number>;
        get extras(): number;
        get defaultExtras(): number;
        get hasAutoAttachTrailer(): boolean;
        get bones(): ReadonlyArray<BoneInfo>;

        static get(model: string | number): VehicleModelInfo;
    }

    export class WorldObject extends shared.BaseObject {
        // Shared
        get pos(): shared.Vector3;

        // Server
        set pos(pos: shared.Vector3): void;
        get dimension(): number;
    }

    export class Entity extends WorldObject {
        // Shared
        get id(): number;
        get model(): number;
        get netOwner(): Player | null;
        get rot(): shared.Vector3;
        get visible(): boolean;

        get syncedMeta(): Record<string, any>;
        get streamSyncedMeta(): Record<string, any>;

        static get all(): ReadonlyArray<Entity>;

        // Server
        setNetOwner(player: Player, disableMigration?: boolean): void;
        resetNetOwner(disableMigration?: boolean): void;

        attachTo(entity: Entity, entityBone: number | string, ownBone: number | string, pos: shared.Vector3, rot: shared.Vector3, enableCollisions: boolean, noFixedRotation: boolean): void;
        detach(): void;

        set visible(visible: boolean): void;
        set streamed(streamed: boolean): void;
        set frozen(frozen: boolean): void;
        set collision(collision: boolean): void;

        static getByID(id: number): Entity | null;
    }

    export class Player extends Entity {
        // Shared
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
        get aimPos(): shared.Vector3;
        get headRotation(): shared.Vector3;
        get isInVehicle(): boolean;
        get vehicle(): Vehicle | null;
        get seat(): number;
        get entityAimingAt(): Entity | null;
        get entityAimOffset(): shared.Vector3;
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

        static get all(): ReadonlyArray<Player>;

        // Server
        emit(eventName: string, ...args: any[]): void;
        emitUnreliable(eventName: string, ...args: any[]): void;

        // todo: add missing api

        static getByID(id: number): Player | null;
    }

    export class Vehicle extends Entity {
        // Shared
        // todo: add missing api

        static get all(): ReadonlyArray<Vehicle>;

        // Server
        // todo: add missing api
        static getByID(id: number): Vehicle | null;
    }

    export class Blip extends WorldObject {
        // Shared
        get id(): number;
        get isGlobal(): boolean;
        get target(): Entity | null;
        get isAttached(): boolean;
        get attachedTo(): Entity | null;
        get blipType(): shared.Enums.BlipType;

        scale: shared.Vector2;
        display: number;
        sprite: number;
        color: number;
        secondaryColor: shared.RGBA;
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
        routeColor: shared.RGBA;
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

    interface PointBlipCreateArgs {
        pos?: shared.Vector3;
        entity?: Entity;
    }
    export namespace PointBlip {
        export function create(args: PointBlipCreateArgs): Blip;
    }

    interface AreaBlipCreateArgs {
        pos: shared.Vector3;
        scale: shared.Vector2;
    }
    export namespace AreaBlip {
        export function create(args: AreaBlipCreateArgs): Blip;
    }

    interface RadiusBlipCreateArgs {
        pos: shared.Vector3;
        radius: number;
    }
    export namespace RadiusBlip {
        export function create(args: RadiusBlipCreateArgs): Blip;
    }

    interface NetworkObjectCreateArgs {
        model: number | string;
        pos: shared.Vector3;
        rot?: shared.Vector3;
        alpha?: number;
        textureVariation?: number;
        lodDistance?: number;
    };
    export class NetworkObject extends Entity {
        // Shared
        get alpha(): number;
        get textureVariation(): number;
        get lodDistance(): number;

        static get all(): ReadonlyArray<NetworkObject>;

        // Server
        static create(args: NetworkObjectCreateArgs): NetworkObject;
        static getByID(id: number): NetworkObject | null;
    }

    interface PedCreateArgs {
        model: number | string;
        pos: shared.Vector3;
        rot: shared.Vector3;
    }
    export class Ped extends Entity {
        // Shared
        get health(): number;
        get maxHealth(): number;
        get armour(): number;
        get currentWeapon(): number;

        static get all(): ReadonlyArray<Ped>;

        // Server
        static create(args: PedCreateArgs): Ped;
        static getByID(id: number): Ped | null;
    }

    // todo: colshapes

    export * from "@altv/shared";
}
