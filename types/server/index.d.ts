/// <reference types="../shared/index.d.ts" />

/**
 * @module @altv/server
 */

declare module "@altv/server" {
    import altShared from "@altv/shared";

    export const rootDir: string;
    export const defaultDimension: number;
    export const globalDimension: number;

    export const syncedMeta: Record<string, unknown>;
    export const serverConfig: Readonly<Record<string, unknown>>;

    export function getNetTime(): number;

    export function setServerPassword(password: string): void;
    export function hashServerPassword(password: string): number;
    export function stopServer(): void;
    export function toggleWorldProfiler(state: boolean): void;
    export function getEntitiesInDimension(dimension: number, entityType: altShared.Enums.BaseObjectType): ReadonlyArray<altShared.BaseObject>;
    export function getEntitiesInRange(pos: altShared.IVector3, range: number, dimension: number, entityType: altShared.Enums.BaseObjectType): ReadonlyArray<altShared.BaseObject>;
    export function getClosestEntities(pos: altShared.IVector3, range: number, dimension: number, maxCount: number, entityType: altShared.Enums.BaseObjectType): ReadonlyArray<altShared.BaseObject>;

    export function setVoiceExternalPublic(host: string, port: number): void;
    export function setVoiceExternal(host: string, port: number): void;

    export function getMaxStreamingPeds(): number;
    export function getMaxStreamingObjects(): number;
    export function getMaxStreamingVehicles(): number;

    export function setMaxStreamingPeds(limit: number): void;
    export function setMaxStreamingObjects(limit: number): void;
    export function setMaxStreamingVehicles(limit: number): void;
    export function getStreamerThreadCount(): number;
    export function setStreamerThreadCount(count: number): void;
    export function getMigrationThreadCount(): number;
    export function getSyncSendThreadCount(): number;
    export function getSyncReceiveThreadCount(): number;
    export function setMigrationThreadCount(count: number): void;
    export function setSyncSendThreadCount(count: number): void;
    export function setSyncReceiveThreadCount(count: number): void;
    export function getStreamingTickRate(): number;
    export function getMigrationTickRate(): number;
    export function getColShapeTickRate(): number;
    export function setStreamingTickRate(rate: number): void;
    export function setMigrationTickRate(rate: number): void;
    export function setColShapeTickRate(rate: number): void;
    export function getMigrationDistance(): number;
    export function setMigrationDistance(distance: number): void;

    export class BaseObject extends altShared.BaseObject {
        readonly meta: BaseObjectMeta;
        readonly syncedMeta: Readonly<altShared.BaseObjectSyncedMeta>;

        static getByID(type: altShared.Enums.BaseObjectType, id: number): BaseObject | null;
    }

    interface SharedBlipCreateOptions {
        global: boolean;
        targets?: Array<Entity>;

        blipType: altShared.Enums.BlipType;
    }

    export type PointBlipCreateOptions = { pos: altShared.IVector3; entity?: never } | { entity: Entity; pos?: never };

    type BlipCreateOptions = SharedBlipCreateOptions &
        (({ blipType: altShared.Enums.BlipType.AREA } & altShared.AreaBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.RADIUS } & altShared.RadiusBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.DESTINATION } & PointBlipCreateOptions));

    export abstract class Blip extends BaseObject {
        readonly targets: ReadonlyArray<Player>;

        readonly scriptID: number;
        readonly isStreamedIn: boolean;
        readonly isAttached: boolean;
        readonly attachedTo?: Entity;

        global: boolean;

        blipType: altShared.Enums.BlipType;
        scale: altShared.Vector2;
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
        routeColor: altShared.RGBA;
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
        addTarget(target: Player): void;
        removeTarget(target: Player): void;

        readonly meta: BlipMeta;
        readonly syncedMeta: altShared.BlipSyncedMeta;

        static getByID(id: number): Blip | null;
        static create(opts: BlipCreateOptions): Blip | null;
    }

    export namespace PointBlip {
        export function create(opts: PointBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export namespace AreaBlip {
        export function create(opts: altShared.AreaBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export namespace RadiusBlip {
        export function create(opts: altShared.RadiusBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export abstract class ColShape extends WorldObject {
        readonly colShapeType: altShared.Enums.ColShapeType;
        playersOnly: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: altShared.Vector3): boolean;

        readonly meta: ColShapeMeta;
        readonly syncedMeta: altShared.ColShapeSyncedMeta;
    }

    export abstract class Checkpoint extends ColShape {
        readonly isStreamedIn: boolean;

        checkpointType: number;
        radius: number;
        height: number;
        color: altShared.RGBA;
        iconColor: altShared.RGBA;
        nextPos: altShared.IVector3;
        readonly streamingDistance: number;
        visible: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: altShared.Vector3): boolean;

        readonly meta: CheckpointMeta;
        readonly syncedMeta: altShared.CheckpointSyncedMeta;
        readonly streamSyncedMeta: altShared.CheckpointStreamSyncedMeta;

        static create(opts: altShared.CheckpointCreateOptions): Checkpoint | null;
        static getByID(id: number): Checkpoint | null;
    }

    export abstract class Entity extends WorldObject {
        get model(): number;
        netOwner?: Player;

        rot: altShared.Vector3;

        visible: boolean;
        streamed: boolean;
        frozen: boolean;
        collision: boolean;
        readonly timestamp: number;

        readonly meta: EntityMeta;
        readonly syncedMeta: altShared.EntitySyncedMeta;
        readonly streamSyncedMeta: altShared.EntityStreamSyncedMeta;

        setNetOwner(player: Player, disableMigration: boolean): void;
        resetNetOwner(disableMigration: boolean): void;

        attachTo(target: Entity, otherBoneId: number | string, boneId: number | string, pos: altShared.IVector3, rot: altShared.IVector3, collision: boolean, noFixedRot: boolean): void;
        detach(): void;

        static readonly all: ReadonlyArray<Entity>;
    }

    export class Metric {
        readonly name: string;
        value: number;
        readonly valid: boolean;

        constructor(name: string, type?: altShared.Enums.MetricType);

        begin(): void;
        end(): void;
        destroy(): void;
    }

    interface ObjectCreateOptions {
        model: number | string;
        pos: altShared.IVector3;
        rot?: altShared.IVector3; // default: { x: 0, y: 0, z: 0 }
        alpha?: number; // default: 255
        textureVariation?: number; // default: 0
        lodDistance?: number; // default: 100
    }

    export abstract class Object extends Entity {
        alpha: number;
        textureVariation: number;
        lodDistance: number;

        activatePhysics(): void;
        placeOnGroundProperly(): void;

        readonly meta: ObjectMeta;
        readonly syncedMeta: altShared.ObjectSyncedMeta;
        readonly streamSyncedMeta: altShared.ObjectStreamSyncedMeta;

        static getByID(id: number): Object | null;
        static create(opts: ObjectCreateOptions): Object | null;
        static readonly all: ReadonlyArray<Object>;
    }

    interface PedCreateOptions {
        model: number | string;
        pos: altShared.IVector3;
        heading: number;
    }

    export abstract class Ped extends Entity {
        health: number;
        maxHealth: number;
        armour: number;
        currentWeapon: number;

        readonly meta: PedMeta;
        readonly syncedMeta: altShared.PedSyncedMeta;
        readonly streamSyncedMeta: altShared.PedStreamSyncedMeta;

        static getByID(id: number): Ped | null;
        static create(opts: PedCreateOptions): Ped | null;
        static readonly all: ReadonlyArray<Ped>;
    }

    export class Player extends Entity {
        readonly name: string;

        readonly ip: string;
        readonly socialId: number;
        readonly hwidHash: number;
        readonly hwidExHash: number;

        readonly isConnected: boolean;
        readonly authToken: string;
        readonly discordId: number;

        get model(): number;
        set model(value: number | string);

        armour: number;
        maxArmour: number;

        health: number;
        maxHealth: number;
        invincible: boolean;

        readonly currentWeaponComponents: ReadonlyArray<number>;
        readonly currentWeaponTintIndex: number;
        get currentWeapon(): number;
        set currentWeapon(value: number | string);
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
        readonly moveSpeed: number;
        readonly aimPos: altShared.Vector3;
        readonly headRotation: altShared.Vector3;
        readonly isInVehicle: boolean;
        readonly vehicle?: Vehicle;
        readonly seat: number;
        readonly entityAimingAt: Entity;
        readonly entityAimOffset: altShared.Vector3;
        readonly isFlashlightActive: boolean;
        readonly isSuperJumpEnabled: boolean;
        readonly isCrouching: boolean;
        readonly isStealthy: boolean;
        readonly currentAnimationDict: number;
        readonly currentAnimationName: number;
        readonly isSpawned: boolean;
        readonly forwardSpeed: number;
        readonly strafeSpeed: number;

        headBlendData: altShared.Appearance.HeadBlendData;
        eyeColor: number;
        hairColor: number;
        hairHighlightColor: number;

        readonly weapons: ReadonlyArray<altShared.WeaponInfo>;

        readonly interiorLocation: number;
        readonly lastDamagedBodyPart: number;
        sendNames: boolean;

        readonly cloudAuthHash: string;
        netOwnershipDisabled: boolean;

        emit<E extends keyof altShared.Events.CustomServerToPlayerEvent>(event: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;
        emitRaw<E extends keyof altShared.Events.CustomServerToPlayerEvent>(event: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;
        emitUnreliable<E extends keyof altShared.Events.CustomServerToPlayerEvent>(event: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;
        spawn(pos: altShared.IVector3, delay?: number): void;
        despawn(): void;
        setWeaponTintIndex(weaponHash: number | string, tintIndex: number): void;
        addWeaponComponent(weaponHash: number | string, componentHash: number | string): void;
        getWeaponTintIndex(weaponHash: number | string): number | undefined;
        hasWeaponComponent(weaponHash: number | string, componentHash: number | string): boolean;
        removeWeaponComponent(weaponHash: number | string, componentHash: number | string): void;
        clearBloodDamage(): void;
        giveWeapon(weaponHash: number | string, ammo: number, selectWeapon?: boolean): void;
        removeWeapon(weaponHash: number | string): void;
        removeAllWeapons(): void;
        setDateTime(day: number, month: number, year: number, hour: number, minute: number, second: number): void;
        setWeather(weather: number): void;

        kick(reason?: string): void;

        getClothes(componentId: number): altShared.Appearance.Clothing;
        setClothes(componentId: number, drawable: number, texture: number, palette: number): boolean;
        getDlcClothes(componentId: number): altShared.Appearance.DlcClothing;
        setDlcClothes(componentId: number, drawable: number, texture: number, palette: number, dlc: number): boolean;
        getProps(componentId: number): altShared.Appearance.Prop;
        setProps(componentId: number, drawable: number, texture: number): boolean;
        getDlcProps(componentId: number): altShared.Appearance.DlcProp;
        setDlcProps(componentId: number, drawable: number, texture: number, dlc: number): boolean;
        clearProps(componentId: number): void;

        // TODO (xLuxy): Add Entity as argument
        isEntityInStreamingRange(entityId: number): boolean;
        setIntoVehicle(vehicle: Vehicle, seat: number): void;
        playAmbientSpeech(speechName: string, speechParam: string, speechDictHash: number): void;

        setHeadOverlay(overlayId: number, index: number, opacity: number): boolean;
        removeHeadOverlay(overlayId: number): boolean;
        setHeadOverlayColor(overlayId: number, colorType: number, colorIndex: number, secondColorIndex: number): boolean;

        getHeadOverlay(overlayId: number): altShared.Appearance.HeadOverlay | undefined;

        setFaceFeature(index: number, scale: number): boolean;
        getFaceFeature(index: number): number;
        removeFaceFeature(index: number): boolean;

        setHeadBlendPaletteColor(id: number, colorOrRed: altShared.RGBA | number, green?: number, blue?: number): boolean;
        getHeadBlendPaletteColor(id: number): altShared.RGBA;

        playAnimation(animDict: string, animName: string, blendInSpeed?: number, blendOutSpeed?: number, duration?: number, flag?: number, playbackRate?: number, lockX?: boolean, lockY?: boolean, lockZ?: boolean): void;
        clearTasks(): void;

        hasWeapon(weaponHash: number | string): boolean;
        getAmmo(ammoHash: number | string): number | undefined;
        setAmmo(ammoHash: number | string, ammo: number): void;
        getWeaponAmmo(weaponHash: number | string): number | undefined;
        setWeaponAmmo(weaponHash: number | string, ammo: number): void;

        getAmmoSpecialType(ammoHash: number | string): number;
        setAmmoSpecialType(ammoHash: number | string, specialType: altShared.Enums.AmmoSpecialType): void;

        getAmmoFlags(ammoHash: number | string): altShared.AmmoData;
        setAmmoFlags(flags: altShared.AmmoData & { ammoHash: string }): void;
        getAmmoMax(ammoHash: number | string): number | undefined;
        setAmmoMax(ammoHash: number | string, ammo: number): void;
        getAmmoMax50(ammoHash: number | string): number | undefined;
        setAmmoMax50(ammoHash: number | string, ammo: number): void;
        getAmmoMax100(ammoHash: number | string): number | undefined;
        setAmmoMax100(ammoHash: number | string, ammo: number): void;
        addDecoration(collection: number | string, overlay: number | string): void;
        removeDecoration(collection: number | string, overlay: number | string): void;
        clearDecorations(): void;
        getDecorations(): ReadonlyArray<{ collection: number; overlay: number }>;
        playScenario(name: string): void;
        requestCloudID(): Promise<string>;

        readonly meta: PlayerMeta;
        readonly syncedMeta: altShared.PlayerSyncedMeta;
        readonly streamSyncedMeta: altShared.PlayerStreamSyncedMeta;

        static readonly all: ReadonlyArray<Player>;
        static getByID(id: number): Player | null;
    }

    export abstract class Resource extends altShared.Resource {
        readonly clientType: string;
        readonly clientMain: string;
        readonly clientFiles: ReadonlyArray<string>;

        getMatchedFiles(pattern: string): ReadonlyArray<string>;

        static start(resourceName: string): void;
        static stop(resourceName: string): void;
        static restart(resourceName: string): void;
    }

    interface VehicleCreateOptions {
        model: number | string;
        pos: altShared.IVector3;
        rot?: altShared.IVector3; // default: { x: 0, y: 0, z: 0 }
    }

    export abstract class Vehicle extends Entity {
        readonly neon: altShared.NeonState;
        readonly driver?: Player;
        readonly isDestroyed: boolean;
        readonly modKitsCount: number;
        readonly IsPrimaryColorRGB: boolean;
        readonly primaryColorRGB: altShared.RGBA;
        readonly isSecondaryColorRGB: boolean;
        readonly secondaryColorRGB: altShared.RGBA;
        readonly isTireSmokeColorCustom: boolean;
        readonly wheelType: number;
        readonly wheelVariation: number;
        readonly isNeonActive: boolean;
        readonly isEngineOn: boolean;
        readonly isHandbrakeActive: boolean;
        readonly isSirenActive: boolean;
        readonly isDaylightOn: boolean;
        readonly isNightlightOn: boolean;
        readonly isFlamethrowerActive: boolean;
        readonly gameStateBase64: string;
        readonly wheelsCount: number;
        readonly repairsCount: number;
        readonly hasArmoredWindows: boolean;
        readonly isManualEngineControl: boolean;
        readonly velocity: altShared.Vector3;
        readonly steeringAngle: number;

        modKit: number;
        primaryColor: number;
        customPrimaryColor: altShared.RGBA;
        secondaryColor: number;
        customSecondaryColor: altShared.RGBA;
        pearlColor: number;
        wheelColor: number;
        interiorColor: number;
        dashboardColor: number;
        tireSmokeColor: altShared.RGBA;
        customTires: boolean;
        specialDarkness: number;
        numberplateIndex: number;
        numberplateText: string;
        windowTint: number;
        dirtLevel: number;
        neonColor: altShared.RGBA;
        livery: number;
        roofLivery: number;
        appearanceDataBase64: string;
        engineOn: boolean;
        headlightColor: number;
        radioStationIndex: number;
        sirenActive: boolean;
        lockState: number;
        roofState: number;
        lightsMultiplier: number;
        engineHealth: number;
        petrolTankHealth: number;
        bodyHealth: number;
        bodyAdditionalHealth: number;
        manualEngineControl: number;
        damageDataBase64: string;
        scriptDataBase64: string;
        gameStateDataBase64: string;
        healthDataBase64: string;
        attached?: Vehicle;
        attachedTo?: Vehicle;
        driftMode: boolean;

        isMissionTrain: boolean;
        trainTrackId: number;
        trainEngine?: Vehicle;
        trainConfigIndex: number;
        hasTrainEngine: boolean;
        isTrainCaboose: boolean;
        trainDirection: boolean;
        hasTrainPassengerCarriages: boolean;
        trainCruiseSpeed: number;
        trainCarriageConfigIndex: number;
        trainLinkedToBackward?: Vehicle;
        trainLinkedToForward?: Vehicle;
        trainUnk1: boolean;
        trainUnk2: boolean;
        trainUnk3: boolean;

        boatAnchorActive: boolean;
        lightState: number;

        readonly hasTimedExplosion: boolean;
        readonly timedExplosionCulprit?: Player;
        readonly timedExplosionTime: number;

        towingDisabled: boolean;
        rocketRefuelSpeed: number;
        counterMeasureCount: number;
        scriptMaxSpeed: number;
        hybridExtraActive: boolean;
        hybridExtraState: number;

        quaternion: altShared.Quaternion;
        readonly isHornActive: boolean;
        readonly accelerationLevel: number;
        readonly brakeLevel: number;

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

        repair(): void;
        setMod(category: number, id: number): boolean;
        setWheels(type: number, variation: number): void;
        setDoorState(doorId: number, state: number): void;
        setWindowOpened(windowId: number, state: boolean): void;
        setWheelBurst(wheelId: number, state: boolean): void;
        setWheelDetached(wheelId: number, state: boolean): void;
        setWheelOnFire(wheelId: number, state: boolean): void;
        setWheelHealth(wheelId: number, health: number): void;
        setWheelFixed(wheelId: number): void;

        setPartDamageLevel(partId: number, damage: number): void;
        setPartBulletHoles(partId: number, shootsCount: number): void;
        setLightDamaged(lightId: number, isDamaged: boolean): void;
        setWindowDamaged(windowId: number, isDamaged: boolean): void;
        setSpecialLightDamaged(specialLightId: number, isDamaged: boolean): void;
        setArmoredWindowHealth(windowId: number, health: number): void;
        setArmoredWindowShootCount(windowId: number, count: number): void;
        setBumperDamageLevel(bumperId: number, damageLevel: number): void;
        setSearchLight(state: number, spottedEntity: Entity): boolean;
        setTimedExplosion(state: boolean, culprit: Player, time: number): void;
        getWeaponCapacity(index: number): number;
        setWeaponCapacity(index: number, state: number): void;

        readonly meta: VehicleMeta;
        readonly syncedMeta: altShared.VehicleSyncedMeta;
        readonly streamSyncedMeta: altShared.VehicleStreamSyncedMeta;

        static getByID(id: number): Vehicle | null;
        static create(opts: VehicleCreateOptions): Vehicle | null;
        static all: ReadonlyArray<Vehicle>;
    }

    interface VirtualEntityCreateOptions {
        group: VirtualEntityGroup;
        pos: altShared.IVector3;
        maxEntitiesInStream: number;
        data?: Record<string, unknown>;
    }

    export abstract class VirtualEntityGroup extends BaseObject {
        readonly maxEntitiesInStream: number;

        static create(opts: altShared.VirtualEntityGroupCreateOptions): VirtualEntityGroup | null;
    }

    export abstract class VirtualEntity extends WorldObject {
        readonly isStreamedIn: boolean;

        readonly group: VirtualEntityGroup;
        readonly streamingDistance: number;

        visible: boolean;

        readonly meta: VirtualEntityMeta;
        readonly syncedMeta: altShared.VirtualEntitySyncedMeta;
        readonly streamSyncedMeta: altShared.VirtualEntityStreamSyncedMeta;

        static create(opts: VirtualEntityCreateOptions): VirtualEntity | null;
    }

    interface VoiceChannelCreateOptions {
        spatial: boolean;
        maxDistance?: number;
    }

    export abstract class VoiceChannel extends BaseObject {
        readonly isSpatial: boolean;
        readonly maxDistance: number;

        readonly players: ReadonlyArray<Player>;
        readonly playerCount: number;

        hasPlayer(player: Player): boolean;
        addPlayer(player: Player): void;
        removePlayer(player: Player): void;

        isPlayerMuted(player: Player): boolean;
        mutePlayer(player: Player): void;
        unmutePlayer(player: Player): void;

        static create(opts: VoiceChannelCreateOptions): VoiceChannel | null;
    }

    export abstract class WorldObject extends BaseObject {
        dimension: number;
        pos: altShared.Vector3;
    }

    export interface BoneInfo {
        id: number;
        index: number;
        name: string;
    }

    export interface PedModelInfo {
        hash: number;
        name: string;
        type: string;
        dlcName: string;
        defaultUnarmedWeapon: string;
        movementClipSet: string;
        bones: BoneInfo[];
    }

    export interface VehicleModelInfo {
        model: number;
        title: string;
        modelType: altShared.Enums.VehicleModelType;
        wheelsCount: number;
        hasArmoredWindows: boolean;
        primaryColor: number;
        secondaryColor: number;
        pearlColor: number;
        wheelsColor: number;
        interiorColor: number;
        dashboardColor: number;
        modkits: number[];
        extras: number;
        defaultExtras: number;
        hasAutoAttachTrailer: boolean;
        bones: BoneInfo[];
        canAttachCars: boolean;

        doesExtraExist(extraId: number): boolean | undefined;
        isExtraDefault(extraId: number): boolean | undefined;
    }

    export interface WeaponModelInfo {
        hash: number;
        name: string;
        modelName: string;
        modelHash: number;
        ammoTypeHash: number;
        ammoType: string;
        ammoModelHash: number;
        ammoModelName: string;
        defaultMaxAmmoMp: number;
        skillAbove50MaxAmmoMp: number;
        maxSkillMaxAmmoMp: number;
        bonusMaxAmmoMp: number;
    }

    export namespace PedModelInfo {
        export function get(modelHash: number | string): PedModelInfo | undefined;
    }

    export namespace VehicleModelInfo {
        export function get(modelHash: number | string): VehicleModelInfo | undefined;
    }

    export namespace WeaponModelInfo {
        export function get(weaponHash: number | string): WeaponModelInfo | undefined;
    }

    export namespace Events {
        export let rawEmitEnabled: boolean;
        export function emit<E extends keyof CustomServerEvent>(event: E, ...args: Parameters<CustomServerEvent[E]>): void;

        export function emitPlayers<E extends keyof altShared.Events.CustomServerToPlayerEvent>(players: Player[], eventName: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;
        export function emitPlayersUnreliable<E extends keyof altShared.Events.CustomServerToPlayerEvent>(players: Player[], eventName: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;

        export function emitAllPlayers<E extends keyof altShared.Events.CustomServerToPlayerEvent>(eventName: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;
        export function emitAllPlayersUnreliable<E extends keyof altShared.Events.CustomServerToPlayerEvent>(eventName: E, ...args: Parameters<altShared.Events.CustomServerToPlayerEvent[E]>): void;

        // Server related events
        export function onServerStarted(callback: GenericEventCallback): void;

        // TODO (xLuxy): Not implemented
        export function onConnectionQueueAdd(callback: GenericEventCallback<ConnectionQueueEventParameters>): void;
        // TODO (xLuxy): Not implemented
        export function onConnectionQueueRemove(callback: GenericEventCallback<ConnectionQueueEventParameters>): void;

        // Player related events
        export function onPlayerConnect(callback: GenericPlayerEventCallback<PlayerConnectEventParameters>): void;
        export function onPlayerConnectDenied(callback: GenericEventCallback<PlayerConnectDeniedEventParameters>): void;
        export function onPlayerDisconnect(callback: GenericPlayerEventCallback<PlayerDisconnectEventParameters>): void;
        export function onPlayerDamage(callback: GenericPlayerEventCallback<PlayerDamageEventParameters>): void;
        export function onPlayerDeath(callback: GenericPlayerEventCallback<PlayerDeathEventParameters>): void;
        export function onPlayerHeal(callback: GenericPlayerEventCallback<PlayerHealEventParameters>): void;
        export function onPlayerControlRequest(callback: GenericPlayerEventCallback<PlayerControlRequestEventParameters>): void;
        export function onPlayerInteriorChange(callback: GenericPlayerEventCallback<PlayerInteriorChangeEventParameters>): void;
        export function onPlayerDimensionChange(callback: GenericPlayerEventCallback<PlayerDimensionChangeEventParameters>): void;
        export function onPlayerWeaponChange(callback: GenericPlayerEventCallback<PlayerWeaponChangeEventParameters>): void;
        export function onPlayerSyncedSceneRequest(callback: GenericEventCallback<PlayerSyncedSceneRequestEventParameters>): void;
        export function onPlayerSyncedSceneStart(callback: GenericPlayerEventCallback<PlayerSyncedSceneStartEventParameters>): void;
        export function onPlayerSyncedSceneStop(callback: GenericPlayerEventCallback<PlayerSyncedSceneStopEventParameters>): void;
        export function onPlayerSyncedSceneUpdate(callback: GenericPlayerEventCallback<PlayerSyncedSceneUpdateEventParameters>): void;
        export function onPlayerSpawn(callback: GenericPlayerEventCallback): void;
        export function onPlayerAnimationChange(callback: GenericPlayerEventCallback<PlayerAnimationChangeEventParameters>): void;
        export function onPlayerEnteredVehicle(callback: GenericPlayerEventCallback<PlayerEnteredVehicleEventParameters>): void;
        export function onPlayerEnteringVehicle(callback: GenericPlayerEventCallback<PlayerEnteringVehicleEventParameters>): void;
        export function onPlayerLeftVehicle(callback: GenericPlayerEventCallback<PlayerLeftVehicleEventParameters>): void;
        export function onPlayerVehicleSeatChange(callback: GenericPlayerEventCallback<PlayerVehicleSeatChangeEventParameters>): void;

        // Vehicle related events
        export function onVehicleDestroy(callback: GenericEventCallback<VehicleDestroyEventParameters>): void;
        export function onVehicleAttach(callback: GenericEventCallback<VehicleAttachEventParameters>): void;
        export function onVehicleDetach(callback: GenericEventCallback<VehicleDetachEventParameters>): void;
        export function onVehicleDamage(callback: GenericEventCallback<VehicleDamageEventParameters>): void;
        export function onVehicleSirenStateChange(callback: GenericEventCallback<VehicleSirenStateChangeEventParameters>): void;
        export function onVehicleHornStateChange(callback: GenericPlayerEventCallback<VehicleHornStateChangeEventParameters>): void;

        // Voice related events
        export function onVoiceConnectionCreate(callback: GenericEventCallback<VoiceConnectionEventParameters>): void;

        // Object related events
        export function onClientObjectDelete(callback: GenericPlayerEventCallback): void;
        export function onClientObjectRequest(callback: GenericPlayerEventCallback<ClientObjectEventParameters>): void;

        // SHARED Entity related events
        export function onBaseObjectCreate(callback: GenericEventCallback<BaseObjectCreateEventParameters>): void;
        export function onBaseObjectRemove(callback: GenericEventCallback<BaseObjectRemoveEventParameters>): void;
        export function onNetOwnerChange(callback: GenericEventCallback<NetOwnerChangeEventParameters>): void;
        export function onWeaponDamage(callback: GenericEventCallback<WeaponDamageEventParameters>): void;

        // SHARED meta related events
        export function onLocalMetaChange(callback: GenericPlayerEventCallback<LocalMetaChangeEventParameters>): void;
        export function onSyncedMetaChange(callback: GenericEventCallback<SyncedMetaChangeEventParameters>): void;
        export function onStreamSyncedMetaChange(callback: GenericEventCallback<StreamSyncedMetaChangeEventParameters>): void;
        export function onGlobalMetaChange(callback: GenericEventCallback<GlobalMetaChangeEventParameters>): void;
        export function onGlobalSyncedMetaChange(callback: GenericEventCallback<GlobalSyncedMetaChangeEventParameters>): void;

        // SHARED custom events
        export function onConsoleCommand(callback: GenericEventCallback<ConsoleCommandEventParameters>): void;
        export function onError(callback: GenericEventCallback<ErrorEventParameters>): void;

        // Script related events
        export function onColShapeEvent(callback: GenericEventCallback<ColShapeEventParameters>): void;
        export function onExplosion(callback: GenericEventCallback<ExplosionEventParameters>): void;
        export function onFireStart(callback: GenericPlayerEventCallback<FireStartEventParameters>): void;
        export function onProjectileStart(callback: GenericPlayerEventCallback<ProjectileStartEventParameters>): void;
        export function onEntityColShapeEnter(callback: GenericEventCallback<EntityColShapeEnterEventParameters>): void;
        export function onEntityColShapeLeave(callback: GenericEventCallback<EntityColShapeLeaveEventParameters>): void;
        export function onEntityCheckpointEnter(callback: GenericEventCallback<EntityCheckpointEnterEventParameters>): void;
        export function onEntityCheckpointLeave(callback: GenericEventCallback<EntityCheckpointLeaveEventParameters>): void;

        // SHARED script related events
        export function onLocalScriptEvent<T = unknown[]>(callback: GenericEventCallback<ServerScriptEventParameters<T>>): void;
        export function onRemoteScriptEvent<T = unknown[]>(callback: GenericPlayerEventCallback<PlayerScriptEventParameters<T>>): void;

        // SHARED resource events
        export function onResourceStart(callback: GenericEventCallback<ResourceStartEventParameters>): void;
        export function onResourceStop(callback: GenericEventCallback<ResourceStopEventParameters>): void;
        export function onResourceError(callback: GenericEventCallback<ResourceErrorEventParameters>): void;

        // Custom events
        export function on<E extends keyof CustomServerEvent>(eventName: E, callback: CustomEventCallback<E, Parameters<CustomServerEvent[E]>>): EventSubscription;
        export function on(callback: CustomEventCallback<string, unknown[]>): EventSubscription;
        export function onPlayer<E extends keyof altShared.Events.CustomPlayerToServerEvent>(eventName: E, callback: CustomPlayerEventCallback<E, Parameters<altShared.Events.CustomPlayerToServerEvent[E]>>): EventSubscription;
        export function onPlayer(eventName: string, callback: CustomPlayerEventCallback<string, unknown[]>): EventSubscription;
        export function onRemote<E extends keyof altShared.Events.CustomPlayerToServerEvent>(eventName: E, callback: CustomPlayerEventCallback<E, Parameters<altShared.Events.CustomPlayerToServerEvent[E]>>): EventSubscription;
        export function onRemote<E extends keyof altShared.Events.CustomRemoteEvent>(eventName: E, callback: CustomPlayerEventCallback<E, Parameters<altShared.Events.CustomRemoteEvent[E]>>): EventSubscription;
        export function onRemote(eventName: string, callback: CustomPlayerEventCallback<string, unknown[]>): EventSubscription;

        export function setWarningThreshold(threshold: number): void;
        export function setSourceLocationFrameSkipCount(skipCount: number): void;

        interface EventSubscription {
            readonly listeners: ReadonlyArray<GenericEventCallback>;
            remove(eventName: string, callback: GenericEventCallback): void;
        }

        export abstract class ConnectionInfo {
            readonly name: string;
            readonly socialId: number;
            readonly socialName: string;
            readonly hwidHash: number;
            readonly hwidExHash: number;
            readonly authToken: string;
            readonly debug: boolean;
            readonly branch: string;
            readonly build: number;
            readonly cdnUrl: string;
            readonly passwordHash: number;
            readonly ip: string;
            readonly discordUserId: number;
            readonly cloudAuthHash: number;

            readonly isAccepted: boolean;
            text: string;

            accept(sendNames?: boolean): void;
            decline(reason: string): void;
        }

        interface ConnectionQueueEventParameters {
            connectionInfo: ConnectionInfo;
        }

        interface PlayerConnectEventParameters {}

        interface PlayerConnectDeniedEventParameters {
            reason: string;
            name: string;
            ip: string;
            passwordHash: number;
            isDebug: boolean;
            branch: string;
            version: string;
            cdnUrl: string;
            discordId: number;
        }

        interface PlayerDisconnectEventParameters {
            reason: string;
        }

        interface PlayerDamageEventParameters {
            attacker?: Entity;
            healthDamage: number;
            armourDamage: number;
            weaponHash: number;
        }

        interface PlayerDeathEventParameters {
            killer?: Entity;
            weaponHash: number;
        }

        interface PlayerHealEventParameters {
            newHealth: number;
            oldHealth: number;
            newArmour: number;
            oldArmour: number;
        }

        interface PlayerControlRequestEventParameters {
            target: Entity;
        }

        interface PlayerInteriorChangeEventParameters {
            oldInterior: number;
            newInterior: number;
        }

        interface PlayerDimensionChangeEventParameters {
            oldDimension: number;
            newDimension: number;
        }

        interface PlayerWeaponChangeEventParameters {
            oldWeapon: number;
            newWeapon: number;
        }

        interface PlayerSyncedSceneRequestEventParameters {
            sceneID: number;
        }

        interface PlayerSyncedSceneStartEventParameters {
            sceneID: number;
            startPos: altShared.Vector3;
            startRot: altShared.Vector3;
            animDict: string;
        }

        interface PlayerSyncedSceneStopEventParameters {
            sceneID: number;
        }

        interface PlayerSyncedSceneUpdateEventParameters {
            sceneID: number;
            startRate: number;
        }

        interface ColShapeEventParameters {
            entity: WorldObject;
            target: ColShape;
            state: boolean;
        }

        interface ExplosionEventParameters {
            source: Player;
            type: altShared.Enums.ExplosionType;
            pos: altShared.Vector3;
            fx: number;
            target?: Entity;
        }

        interface FireStartEventParameters {
            fires: {
                pos: altShared.Vector3;
                weaponHash: number;
            }[];
        }

        interface ProjectileStartEventParameters {
            pos: altShared.Vector3;
            dir: altShared.Vector3;
            ammoHash: number;
            weaponHash: number;
        }

        interface EntityColShapeEnterEventParameters {
            entity: WorldObject;
            colShape: ColShape;
        }

        interface EntityColShapeLeaveEventParameters {
            entity: WorldObject;
            colShape: ColShape;
        }

        interface EntityCheckpointEnterEventParameters {
            entity: WorldObject;
            colShape: ColShape;
        }

        interface EntityCheckpointLeaveEventParameters {
            entity: WorldObject;
            colShape: ColShape;
        }

        interface CustomServerEvent {}

        export type CustomEventCallback<E extends string, T extends unknown[]> = (params: { eventName: E; args: T }) => void | Promise<void>;
        export type CustomPlayerEventCallback<E extends string, T extends unknown[]> = (params: { eventName: E; player: Player; args: T }) => void | Promise<void>;
        export type GenericEventCallback<T extends {} = {}> = (params: T) => void | Promise<void>;
        export type GenericPlayerEventCallback<T extends {} = {}> = (params: T & { player: Player }) => void | Promise<void>;

        interface ServerScriptEventParameters<T> {
            eventName: string;
            args: T;
        }

        interface PlayerScriptEventParameters<T> {
            eventName: string;
            args: T;
        }

        interface PlayerAnimationChangeEventParameters {
            oldAnimDict: number;
            newAnimDict: number;
            oldAnimName: number;
            newAnimName: number;
        }

        interface PlayerEnteredVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerEnteringVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerLeftVehicleEventParameters {
            vehicle: Vehicle;
            seat: number;
        }

        interface PlayerVehicleSeatChangeEventParameters {
            vehicle: Vehicle;
            oldSeat: number;
            newSeat: number;
        }

        interface VehicleDestroyEventParameters {
            vehicle: Vehicle;
        }

        interface VehicleAttachEventParameters {
            vehicle: Vehicle;
            attachedVehicle: Vehicle;
        }

        interface VehicleDetachEventParameters {
            vehicle: Vehicle;
            detachedVehicle: Vehicle;
        }

        interface VehicleDamageEventParameters {
            vehicle: Vehicle;
            attacker: Entity;
            bodyHealthDamage: number;
            additionalBodyHealthDamage: number;
            engineHealthDamage: number;
            petrolTankDamage: number;
            weaponHash: number;
        }

        interface VehicleSirenStateChangeEventParameters {
            vehicle: Vehicle;
            state: boolean;
        }

        interface VehicleHornStateChangeEventParameters {
            vehicle: Vehicle;
            state: boolean;
        }

        interface VoiceConnectionEventParameters {
            state: altShared.Enums.VoiceConnectionState;
        }

        interface ClientObjectEventParameters {
            model: number;
            pos: altShared.Vector3;
        }

        interface BaseObjectCreateEventParameters {
            object: altShared.BaseObject;
        }

        interface BaseObjectRemoveEventParameters {
            object: altShared.BaseObject;
        }

        interface NetOwnerChangeEventParameters {
            entity: Entity;
            oldOwner?: Player;
            newOwner?: Player;
        }

        interface WeaponDamageEventParameters {
            source: Player;
            target: Entity;
            weaponHash: number;
            damage: number;
            offset: number;
            bodyPart: altShared.Enums.BodyPart;

            setDamageValue(value: number): void;
        }

        interface LocalMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface SyncedMetaChangeEventParameters {
            entity: Entity;
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface StreamSyncedMetaChangeEventParameters {
            entity: Entity;
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface GlobalMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface GlobalSyncedMetaChangeEventParameters {
            key: string;
            oldValue: unknown;
            newValue: unknown;
        }

        interface ConsoleCommandEventParameters {
            command: string;
            args: string[];
        }

        interface ErrorEventParameters {
            error: string;
            stack: string;
        }

        interface ResourceStartEventParameters {
            resource: Resource;
        }

        interface ResourceStopEventParameters {
            resource: Resource;
        }

        interface ResourceErrorEventParameters {
            resource: Resource;
        }
    }

    /**
     * Extend it by interface merging for use in meta.
     */
    export interface GlobalMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in BaseObject#meta.
     */
    export interface BaseObjectMeta {
        [key: string]: unknown;
    }

    /**
     * Extend it by interface merging for use in Blip#meta.
     */
    export interface BlipMeta extends BaseObjectMeta {}

    /**
     * Extend it by interface merging for use in ColShape#meta.
     */
    export interface ColShapeMeta extends BaseObjectMeta {}

    /**
     * Extend it by interface merging for use in Checkpoint#meta.
     */
    export interface CheckpointMeta extends ColShapeMeta {}

    /**
     * Extend it by interface merging for use in Entity#meta.
     */
    export interface EntityMeta extends BaseObjectMeta {}

    /**
     * Extend it by interface merging for use in Player#meta.
     */
    export interface PlayerMeta extends EntityMeta {}

    /**
     * Extend it by interface merging for use in Vehicle#meta.
     */
    export interface VehicleMeta extends EntityMeta {}

    /**
     * Extend it by interface merging for use in Ped#meta.
     */
    export interface PedMeta extends EntityMeta {}

    /**
     * Extend it by interface merging for use in Object#meta.
     */
    export interface ObjectMeta extends EntityMeta {}

    /**
     * Extend it by interface merging for use in VirtualEntity#meta.
     */
    export interface VirtualEntityMeta extends BaseObjectMeta {}

    export * from "@altv/shared";
}
