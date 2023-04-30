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
        interface PlayerConnectEventContext extends shared.Events.EventContext {
            readonly player: Player;
        }
        interface PlayerConnectDeniedEventContext extends shared.Events.EventContext {
            readonly reason: ConnectDeniedReason;
            readonly name: string;
            readonly ip: string;
            readonly passwordHash: number;
            readonly isDebug: boolean;
            readonly branch: string;
            readonly version: string;
            readonly cdnUrl: string;
            readonly discordId: string;
        }
        interface PlayerDisconnectEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly reason: string;
        }
        interface PlayerDamageEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly attacker: Entity | null;
            readonly healthDamage: number;
            readonly armourDamage: number;
            readonly weaponHash: number;
        }
        interface PlayerDeathEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly killer: Entity | null;
            readonly weaponHash: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerEnteredVehicleEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleEnteringEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleLeftEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleSeatChangeEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly oldSeat: number;
            readonly newSeat: number;
        }
        interface PlayerWeaponChangeEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly oldWeapon: number;
            readonly newWeapon: number;
        }
        interface PlayerRequestControlEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly target: Entity | null;
        }
        interface PlayerInteriorChangeEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly oldInterior: number;
            readonly newInterior: number;
        }
        interface PlayerDimensionChangeEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly oldDimension: number;
            readonly newDimension: number;
        }
        interface ColshapeEventContext extends shared.Events.EventContext {
            readonly entity: Entity;
            readonly colShape: ColShape;
            readonly state: boolean;
        }
        interface EntityColShapeEventContext extends shared.Events.EventContext {
            readonly entity: Entity;
            readonly colShape: ColShape;
        }
        interface EntityCheckpointEventContext extends shared.Events.EventContext {
            readonly entity: Entity;
            readonly colShape: Checkpoint;
        }
        interface WeaponDamageEventContext extends shared.Events.EventContext {
            readonly source: Player;
            readonly target: Entity;
            readonly weaponHash: number;
            readonly damage: number;
            readonly offset: shared.Vector3;
            readonly bodyPart: shared.Enums.BodyPart;
        }
        interface ExplosionEventContext extends shared.Events.EventContext {
            readonly source: Player;
            readonly type: shared.Enums.ExplosionType;
            readonly pos: shared.Vector3;
            readonly fx: number;
            readonly target: Entity | null;
        }
        interface FireEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly fires: Array<IFireInfo>;
        }
        interface StartProjectileEventContext extends shared.Events.EventContext {
            readonly player: Player;
            readonly pos: shared.Vector3;
            readonly dir: shared.Vector3;
            readonly ammoHash: number;
            readonly weaponHash: number;
        }
        interface VehicleDestroyEventContext extends shared.Events.EventContext {
            vehicle: Vehicle;
        }
        interface VehicleAttachEventContext extends shared.Events.EventContext {
            vehicle: Vehicle;
            attachedVehicle: Vehicle;
        }
        interface VehicleDetachEventContext extends shared.Events.EventContext {
            vehicle: Vehicle;
            detachedVehicle: Vehicle;
        }
        interface VehicleDamageEventContext extends shared.Events.EventContext {
            vehicle: Vehicle;
            attacker: Entity | null;
            bodyHealthDamage: number;
            additionalBodyHealthDamage: number;
            engineHealthDamage: number;
            petrolTankDamage: number;
            weaponHash: number;
        }
        interface VehicleSirenEventContext extends shared.Events.EventContext {
            vehicle: Vehicle;
            state: boolean;
        }

        export const onPlayerConnect: shared.Events.Event<PlayerConnectEventContext>;
        export const onPlayerConnectDenied: shared.Events.Event<PlayerConnectDeniedEventContext>;
        export const onPlayerDisconnect: shared.Events.Event<PlayerDisconnectEventContext>;

        export const onPlayerDamage: shared.Events.Event<PlayerDamageEventContext>;
        export const onPlayerDeath: shared.Events.Event<PlayerDeathEventContext>;

        export const onPlayerEnteredVehicle: shared.Events.Event<PlayerEnteredVehicleEventContext>;
        export const onPlayerVehicleEntering: shared.Events.Event<PlayerVehicleEnteringEventContext>;
        export const onPlayerVehicleLeft: shared.Events.Event<PlayerVehicleLeftEventContext>;
        export const onPlayerVehicleSeatChange: shared.Events.Event<PlayerVehicleSeatChangeEventContext>;

        export const onPlayerWeaponChange: shared.Events.Event<PlayerWeaponChangeEventContext>;

        export const onPlayerRequestControl: shared.Events.Event<PlayerRequestControlEventContext>;

        export const onPlayerInteriorChange: shared.Events.Event<PlayerInteriorChangeEventContext>;
        export const onPlayerDimensionChange: shared.Events.Event<PlayerDimensionChangeEventContext>;

        export const onColshapeEvent: shared.Events.Event<ColshapeEventContext>;
        export const onEntityColShapeEnter: shared.Events.Event<EntityColShapeEventContext>;
        export const onEntityColShapeLeave: shared.Events.Event<EntityColShapeEventContext>;
        export const onEntityCheckpointEnter: shared.Events.Event<EntityCheckpointEventContext>;
        export const onEntityCheckpointLeave: shared.Events.Event<EntityCheckpointEventContext>;

        export const onWeaponDamage: shared.Events.Event<WeaponDamageEventContext>;
        export const onExplosion: shared.Events.Event<ExplosionEventContext>;
        export const onFire: shared.Events.Event<FireEventContext>;
        export const onStartProjectile: shared.Events.Event<StartProjectileEventContext>;

        export const onServerStarted: shared.Events.Event<shared.Events.EventContext>;

        export const onVehicleDestroy: shared.Events.Event<VehicleDestroyEventContext>;
        export const onVehicleAttach: shared.Events.Event<VehicleAttachEventContext>;
        export const onVehicleDetach: shared.Events.Event<VehicleDetachEventContext>;
        export const onVehicleDamage: shared.Events.Event<VehicleDamageEventContext>;
        export const onVehicleSiren: shared.Events.Event<VehicleSirenEventContext>;

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

    export class PedModelInfo {
        get hash(): number;
        get name(): string;
        get type(): number;
        get dlcName(): string;
        get defaultUnarmedWeapon(): string;
        get movementClipSet(): string;
        get bones(): ReadonlyArray<BoneInfo>;

        static get(model: string | number): PedModelInfo;
    }

    export class VehicleModelInfo {
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
        set pos(pos: shared.Vector3);
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

        set visible(visible: boolean);
        set streamed(streamed: boolean);
        set frozen(frozen: boolean);
        set collision(collision: boolean);

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
        get ip(): string;
        get socialId(): number;
        get hwidHash(): number;
        get hwidExHash(): number;
        get isConnected(): boolean;
        get ping(): number;
        get authToken(): string;
        get discordId(): number;

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
    }
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

    export interface IFireInfo {
        readonly pos: shared.Vector3;
        readonly weaponHash: number;
    }

    export class ColShape extends WorldObject {
        // Server
        get colshapeType(): shared.Enums.ColShapeType;
        get playersOnly(): boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(entityID: number): boolean;
        isPointIn(position: shared.Vector3): boolean;
    }

    export const enum ConnectDeniedReason {
        WRONG_VERSION,
        WRONG_BRANCH,
        DEBUG_NOT_ALLOWED,
        WRONG_PASSWORD,
        WRONG_CDN_URL
    }

    export * from "@altv/shared";
}
