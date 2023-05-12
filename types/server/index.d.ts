/**
 * @module @altv/server
 */
declare module "@altv/server" {
    import * as shared from "@altv/shared";

    export const rootDir: string;
    export const netTime: number;
    export const defaultDimension: number;
    export const globalDimension: number;

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

        export const onClient: shared.Events.Event<ClientScriptEventContext>;

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
        get model(): number;
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

        doesExtraExist(extraId: number);
        isExtraDefault(extraId: number);

        static get(model: string | number): VehicleModelInfo;
    }

    export interface BaseObject extends shared.BaseObject {
    }

    export class BaseObject {
    }

    export interface WorldObject extends BaseObject, shared.WorldObject {
        set pos(pos: shared.Vector3);
        dimension: number;
    }

    export class WorldObject {
    }

    export interface Entity extends WorldObject, shared.Entity {
        // Inheritance
        set pos(pos: shared.Vector3);
        // Inheritance End

        setNetOwner(player: Player, disableMigration?: boolean): void;
        resetNetOwner(disableMigration?: boolean): void;

        attachTo(entity: Entity, entityBone: number | string, ownBone: number | string, pos: shared.Vector3, rot: shared.Vector3, enableCollisions: boolean, noFixedRotation: boolean): void;
        detach(): void;

        set visible(visible: boolean);
        streamed: boolean;
        frozen: boolean;
        collision: boolean;
    }

    export class Entity {
        static getByID(id: number): Entity | null;
    }

    export interface Ped extends Entity, shared.Ped {
        // Inheritance
        set pos(pos: shared.Vector3);
        set visible(visible: boolean);
        // Inheritance End

        set health(health: number);
        set maxHealth(maxHealth: number);
        set armour(armour: number);
        set currentWeapon(weapon: number);
    }

    export class Ped {
        static create(args: PedCreateArgs): Ped;
        static getByID(id: number): Ped | null;
    }

    export interface Player extends Entity, shared.Player {
        // Inheritance
        set pos(pos: shared.Vector3);
        set visible(visible: boolean);
        // Inheritance End

        get ip(): string;
        get socialId(): number;
        get hwidHash(): number;
        get hwidExHash(): number;
        get isConnected(): boolean;
        get ping(): number;
        get authToken(): string;
        get discordId(): number;

        set model(model: number | string);
        set armour(armour: number);
        set maxArmour(maxArmour: number);
        set currentWeapon(weapon: number);
        set health(health: number);
        set maxHealth(maxHealth: number);
        invincible: boolean;
        headBlendData: shared.Appearance.HeadblendData;
        eyeColor: number;
        get weapons(): shared.WeaponInfo;
        get interiorLocation(): number;
        get lastDamagedBodyPart(): number;
        sendNames: boolean;
        get cloudAuthHash(): string;

        emit(eventName: string, ...args: any[]): void;
        emitUnreliable(eventName: string, ...args: any[]): void;
        spawn(posiiton: shared.Vector3, timeout?: number): void;
        despawn(): void;
        setWeaponTintIndex(weaponHash: number, tintIndex: number): void;
        addWeaponComponent(weaponHash: number, componentHash: number): void;
        removeWeaponComponent(weaponHash: number, componentHash: number): void;
        clearBloodDamage(): void;
        giveWeapon(weaponHash: number, ammo: number, selectWeapon?: boolean): void;
        removeWeapon(weaponHash: number): void;
        removeAllWeapons(): void;
        setDateTime(day: number, month: number, year: number, hour: number, minute: number, second: number): void;
        setWeather(weatherId: number): void;
        kick(reason: string): void;
        getClothes(component: number): shared.Appearance.Clothing;
        setClothes(component: number, drawable: number, texture: number, palette: number): void;
        getDlcClothes(component: number): shared.Appearance.DlcClothing;
        setDlcClothes(component: number, drawable: number, texture: number, palette: number, dlcHash: number): void;
        getProps(component: number): shared.Appearance.Prop;
        setProps(component: number, drawable: number, texture: number): void;
        getDlcProps(component: number): shared.Appearance.DlcProp;
        setDlcProps(componend: number, drawable: number, texture: number, dlcHash: number): void;
        clearProps(component: number): void;
        isEntityInStreamingRange(entityId: number): void;
        setIntoVehicle(vehicle: shared.Vehicle, seat: number): void;
        playAmbientSpeech(speechName: string, speechParam: string, speechDictHash: number): void;
        setHeadOverlay(overlayId: number, index: number, opacity: number): void;
        removeHeadOverlay(overlay: number): void;
        setHeadOverlayColor(overlay: number, colorType: number, colorIndex: number, secondColorIndex: number): void;
        getHeadOverlay(): shared.Appearance.HeadOverlay;
        setFaceFeature(index: number, scale: number);
        getFaceFeatureScale(index: number): number;
        removeFaceFeature(index: number): void;
        setHeadBlendPaletteColor(color: shared.RGBA): void;
        setHeadBlendPaletteColor(r: number, g: number, b: number, a: number): void;
        getHeadBlendPaletteColor(id: number): shared.RGBA;
        playAnimation(animDict: string, animName: string, blendInSpeed?: number, blendOutSpeed?: number, duration?: number, flag?: number, playbackRate?: number, lockX?: boolean, lockY?: boolean, lockZ?: boolean): void;
        clearTasks(): void;
    }

    export class Player {
        static getByID(id: number): Player | null;
    }

    export interface Vehicle extends Entity, shared.Vehicle {
        // Inheritance
        set pos(pos: shared.Vector3);
        set visible(visible: boolean);
        // Inheritance End

        set modKit(modKit: number);
        set primaryColor(color: number);
        set customPrimaryColor(color: shared.RGBA);
        set secondaryColor(color: number);
        set customSecondaryColor(color: shared.RGBA);
        set pearlColor(color: number);
        set wheelColor(color: number);
        set interiorColor(color: number);
        set dashboardColor(color: number);
        set tireSmokeColor(color: shared.RGBA);
        set customTires(state: boolean);
        set specialDarkness(specialDarkness: number);
        set numberplateIndex(index: number);
        set numberplateText(text: string);
        set windowTint(tint: number);
        set dirtLevel(dirtLevel: number);
        set neonColor(neonColor: shared.RGBA);
        set livery(livery: number);
        set roofLivery(roofLivery: number);
        set appearanceDataBase64(appearanceData: string);
        set engineOn(state: boolean);
        set headlightColor(color: number);
        set radioStationIndex(radioStation: number);
        set isSirenActive(state: boolean);
        set lockState(state: number);
        set roofState(state: number);
        set lightsMultiplier(multiplier: number);
        set engineHealth(health: number);
        set petrolTankHealth(health: number);
        set bodyHealth(health: number);
        set engineHeabodyAdditionalHealthlth(health: number);
        set manualEngineControl(state: boolean);
        set damageDataBase64(damageData: string);
        set scriptDataBase64(scriptrData: string);
        set gameStateDataBase64(gameStateData: string);
        set healthDataBase64(healthData: string);
        get attached(): Vehicle;
        get attachedTo(): Vehicle;
        driftMode: boolean;
        boatAnchorActive: boolean;
        lightState: number;
        get hasTimedExplosion(): boolean;
        get timedExplosionCulprit(): Player;
        get timedExplosionTime(): number;
        towingDisabled: boolean;
        rocketRefuelSpeed: number;
        counterMeasureCount: number;
        scriptMaxSpeed: number;
        hybridExtraActive: boolean;
        hybridExtraState: number;
        quaternion: shared.Quaternion;

        repair(): void;
        setMod(category: number, id: number): void;
        setWheels(type: number, variation: number): void;
        setDoorState(doorId: number, state: boolean): void;
        setWindowOpened(windowId: number, state: boolean): void;
        setWheelBurst(wheelId: number, state: boolean): void;
        setWheelDetached(wheelId: number, state: boolean): void;
        setWheelOnFire(wheelId: number, state: boolean): void;
        setWheelHealth(wheelId: number, health: number): void;
        setWheelFixed(wheelId: number): void;
        setPartDamageLevel(partId: number, damageLevel: number): void;
        setPartBulletHoles(partId: number, shootsCount: number): void;
        setLightDamaged(lightId: number, isDamaged: boolean): void;
        setWindowDamaged(windowId: number, isDamaged: boolean): void;
        setSpecialLightDamaged(lightId: number, isDamaged: boolean): void;
        setArmoredWindowHealth(windowId: number, health: number);
        setArmoredWindowShootCount(windowId: number, shootsCount: number): void;
        setBumperDamageLevel(bumperId: number, damageLevel: number): void;
        setSearchLight(state: boolean, spottedEntity: Entity): void;
        setTimedExplosion(state: boolean, culprit: Player, time: number): void;
        getWeaponCapacity(index: number): void;
        setWeaponCapacity(index: number, state: number): void;
    }

    export class Vehicle {
        static getByID(id: number): Vehicle | null;
    }

    export interface Blip extends BaseObject, shared.Blip {
    }

    export class Blip extends shared.Blip {
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

    export interface NetworkObject extends Entity, shared.NetworkObject {
        // Inheritance
        set pos(pos: shared.Vector3);
        set visible(visible: boolean);
        // Inheritance End

        set alpha(alpha: number);
        set textureVariation(textureVariation: number);
        set lodDistance(lodDistance: number);

        activatePhysics(): void;
        placeOnGroundProperly(): void;
    }

    export class NetworkObject extends shared.NetworkObject {
        static create(args: NetworkObjectCreateArgs): NetworkObject;
        static getByID(id: number): NetworkObject | null;
    }

    interface PedCreateArgs {
        model: number | string;
        pos: shared.Vector3;
        rot: shared.Vector3;
    }

    export interface IFireInfo {
        readonly pos: shared.Vector3;
        readonly weaponHash: number;
    }

    export interface ColShape extends WorldObject, shared.ColShape {
        get colshapeType(): shared.Enums.ColShapeType;
        get playersOnly(): boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(entityID: number): boolean;
        isPointIn(position: shared.Vector3): boolean;
    }

    export class ColShape {
    }

    export interface Checkpoint extends ColShape, shared.Checkpoint {
    }

    export class Checkpoint {
    }

    export const enum ConnectDeniedReason {
        WRONG_VERSION,
        WRONG_BRANCH,
        DEBUG_NOT_ALLOWED,
        WRONG_PASSWORD,
        WRONG_CDN_URL
    }

    export interface VirtualEntityGroup extends BaseObject, shared.VirtualEntityGroup {
    }

    export class VirtualEntityGroup {
    }

    export interface VirtualEntity extends WorldObject, shared.VirtualEntity {
    }

    export class VirtualEntity {
    }

    export class VoiceChannel extends BaseObject {
        get id(): number;
        get isSpatial(): boolean;
        get maxDistance(): number;

        get players(): ReadonlyArray<Player>;
        get playerCount(): number;

        hasPlayer(player: Player): boolean;
        addPlayer(player: Player): void;
        removePlayer(player: Player): void;
        isPlayerMuted(player: Player): boolean;
        mutePlayer(player: Player): void;
        unmutePlayer(player: Player): void;
    }

    export * from "@altv/shared";
}
