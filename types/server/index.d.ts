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
        export interface EventContext {
            cancel(): void;
            readonly isCancelled: boolean;
        }
        export interface Event<Context extends EventContext> {
            (callback: (context: Context) => void): void;

            remove(callback: Callback): void;
            readonly listeners: ReadonlyArray<(context: Context) => void>;
        }

        interface PlayerConnectEventContext extends EventContext {
            readonly player: Player;
        }
        interface PlayerConnectDeniedEventContext extends EventContext {
            readonly reason: shared.Enums.ConnectDeniedReason;
            readonly name: string;
            readonly ip: string;
            readonly passwordHash: number;
            readonly isDebug: boolean;
            readonly branch: string;
            readonly version: string;
            readonly cdnUrl: string;
            readonly discordId: string;
        }
        interface PlayerDisconnectEventContext extends EventContext {
            readonly player: Player;
            readonly reason: string;
        }
        interface PlayerDamageEventContext extends EventContext {
            readonly player: Player;
            readonly attacker: Entity | null;
            readonly healthDamage: number;
            readonly armourDamage: number;
            readonly weaponHash: number;
        }
        interface PlayerDeathEventContext extends EventContext {
            readonly player: Player;
            readonly killer: Entity | null;
            readonly weaponHash: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerEnteredVehicleEventContext extends EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleEnteringEventContext extends EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleLeftEventContext extends EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly seat: number;
        }
        /**
         * @remarks The seat indexes start with 1 (driver seat).
         */
        interface PlayerVehicleSeatChangeEventContext extends EventContext {
            readonly player: Player;
            readonly vehicle: Vehicle;
            readonly oldSeat: number;
            readonly newSeat: number;
        }
        interface PlayerWeaponChangeEventContext extends EventContext {
            readonly player: Player;
            readonly oldWeapon: number;
            readonly newWeapon: number;
        }
        interface PlayerRequestControlEventContext extends EventContext {
            readonly player: Player;
            readonly target: Entity | null;
        }
        interface PlayerInteriorChangeEventContext extends EventContext {
            readonly player: Player;
            readonly oldInterior: number;
            readonly newInterior: number;
        }
        interface PlayerDimensionChangeEventContext extends EventContext {
            readonly player: Player;
            readonly oldDimension: number;
            readonly newDimension: number;
        }
        interface ColshapeEventContext extends EventContext {
            readonly entity: Entity;
            readonly colShape: Colshape;
            readonly state: boolean;
        }
        interface EntityColShapeEventContext extends EventContext {
            readonly entity: Entity;
            readonly colShape: Colshape;
        }
        interface EntityCheckpointEventContext extends EventContext {
            readonly entity: Entity;
            readonly colShape: Checkpoint;
        }
        interface WeaponDamageEventContext extends EventContext {
            readonly source: Player;
            readonly target: Entity;
            readonly weaponHash: number;
            readonly damage: number;
            readonly offset: shared.Vector3;
            readonly bodyPart: shared.Enums.BodyPart;
        }
        interface ExplosionEventContext extends EventContext {
            readonly source: Player;
            readonly type: shared.Enums.ExplosionType;
            readonly pos: shared.Vector3;
            readonly fx: number;
            readonly target: Entity | null;
        }
        interface FireEventContext extends EventContext {
            readonly player: Player;
            readonly fires: Array<IFireInfo>;
        }
        interface StartProjectileEventContext extends EventContext {
            readonly player: Player;
            readonly pos: shared.Vector3;
            readonly dir: shared.Vector3;
            readonly ammoHash: number;
            readonly weaponHash: number;
        }
        interface ConnectionQueueEventContext extends EventContext {
            connectionInfo: IConnectionQueueInfo;
        }
        interface VehicleDestroyEventContext extends EventContext {
            vehicle: Vehicle;
        }
        interface VehicleAttachEventContext extends EventContext {
            vehicle: Vehicle;
            attachedVehicle: Vehicle;
        }
        interface VehicleDetachEventContext extends EventContext {
            vehicle: Vehicle;
            detachedVehicle: Vehicle;
        }
        interface VehicleDamageEventContext extends EventContext {
            vehicle: Vehicle;
            attacker: Entity | null;
            bodyHealthDamage: number;
            additionalBodyHealthDamage: number;
            engineHealthDamage: number;
            petrolTankDamage: number;
            weaponHash: number;
        }
        interface VehicleSirenEventContext extends EventContext {
            vehicle: Vehicle;
            state: boolean;
        }

        export const onPlayerConnect: Event<PlayerConnectEventContext>;
        export const onPlayerConnectDenied: Event<PlayerConnectDeniedEventContext>;
        export const onPlayerDisconnect: Event<PlayerDisconnectEventContext>;

        export const onPlayerDamage: Event<PlayerDamageEventContext>;
        export const onPlayerDeath: Event<PlayerDeathEventContext>;

        export const onPlayerEnteredVehicle: Event<PlayerEnteredVehicleEventContext>;
        export const onPlayerVehicleEntering: Event<PlayerVehicleEnteringEventContext>;
        export const onPlayerVehicleLeft: Event<PlayerVehicleLeftEventContext>;
        export const onPlayerVehicleSeatChange: Event<PlayerVehicleSeatChangeEventContext>;

        export const onPlayerWeaponChange: Event<PlayerWeaponChangeEventContext>;

        export const onPlayerRequestControl: Event<PlayerRequestControlEventContext>;

        export const onPlayerInteriorChange: Event<PlayerInteriorChangeEventContext>;
        export const onPlayerDimensionChange: Event<PlayerDimensionChangeEventContext>;

        export const onColshapeEvent: Event<ColshapeEventContext>;
        export const onEntityColShapeEnter: Event<EntityColShapeEventContext>;
        export const onEntityColShapeLeave: Event<EntityColShapeEventContext>;
        export const onEntityCheckpointEnter: Event<EntityCheckpointEventContext>;
        export const onEntityCheckpointLeave: Event<EntityCheckpointEventContext>;

        export const onWeaponDamage: Event<WeaponDamageEventContext>;
        export const onExplosion: Event<ExplosionEventContext>;
        export const onFire: Event<FireEventContext>;
        export const onStartProjectile: Event<StartProjectileEventContext>;

        export const onServerStarted: Event<EventContext>;

        export const onConnectionQueueAdd: Event<ConnectionQueueEventContext>;
        export const onConnectionQueueRemove: Event<ConnectionQueueEventContext>;

        export const onVehicleDestroy: Event<VehicleDestroyEventContext>;
        export const onVehicleAttach: Event<VehicleAttachEventContext>;
        export const onVehicleDetach: Event<VehicleDetachEventContext>;
        export const onVehicleDamage: Event<VehicleDamageEventContext>;
        export const onVehicleSiren: Event<VehicleSirenEventContext>;

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

    export interface IConnectionInfo {
        readonly name: string;
        readonly socialID: string;
        readonly hwidHash: string;
        readonly hwidExHash: string;
        readonly authToken: string;
        readonly isDebug: boolean;
        readonly branch: string;
        readonly build: number;
        readonly cdnUrl: string;
        readonly passwordHash: string;
        readonly ip: string;
        readonly discordUserID: string;
        readonly socialClubName: string;
        readonly id: number;
        readonly cloudAuthHash: string;
    }

    export interface IConnectionQueueInfo extends IConnectionInfo {
        /**
         * Accepts client connection.
         *
         * @param sendNames Send names of all players on server to this client. Defaults to `true`.
         */
        accept: (sendNames?: boolean) => void;
        decline: (reason: string) => void;
        readonly isAccepted: boolean;
    }

    // todo: colshapes

    export * from "@altv/shared";
}
