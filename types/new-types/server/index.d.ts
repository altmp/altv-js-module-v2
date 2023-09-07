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
    export function getEntitiesInRange(pos: altShared.Vector3, range: number, dimension: number, entityType: altShared.Enums.BaseObjectType): ReadonlyArray<altShared.BaseObject>;
    export function getClosestEntities(pos: altShared.Vector3, range: number, dimension: number, maxCount: number, entityType: altShared.Enums.BaseObjectType): ReadonlyArray<altShared.BaseObject>;

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

    interface SharedBlipCreateOptions {
        global: boolean;
        targets?: Array<Entity>;

        blipType: altShared.Enums.BlipType;
    }

    type BlipCreateOptions = SharedBlipCreateOptions &
        (({ blipType: altShared.Enums.BlipType.AREA } & altShared.AreaBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.RADIUS } & altShared.RadiusBlipCreateOptions) | ({ blipType: altShared.Enums.BlipType.DESTINATION } & altShared.PointBlipCreateOptions));

    export abstract class Blip extends altShared.Blip {
        global: boolean;
        readonly targets: ReadonlyArray<Player>;

        addTarget(target: Player): void;
        removeTarget(target: Player): void;

        static create(opts: BlipCreateOptions): Blip | null;
    }

    export namespace PointBlip {
        export function create(opts: altShared.PointBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export namespace AreaBlip {
        export function create(opts: altShared.AreaBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export namespace RadiusBlip {
        export function create(opts: altShared.RadiusBlipCreateOptions & SharedBlipCreateOptions): Blip | null;
    }

    export abstract class Checkpoint extends altShared.Checkpoint {
        readonly streamSyncedMeta: Record<string, unknown>;
    }

    export abstract class ColShape extends WorldObject {
        readonly colShapeType: altShared.Enums.ColShapeType;
        playersOnly: boolean;

        isEntityIn(entity: Entity): boolean;
        isEntityIdIn(id: number): boolean;
        isPointIn(point: altShared.Vector3): boolean;
    }

    export abstract class Entity extends altShared.Entity {
        visible: boolean;
        streamed: boolean;
        frozen: boolean;
        collision: boolean;
        readonly timestamp: number;

        readonly syncedMeta: Record<string, unknown>;
        readonly streamSyncedMeta: Record<string, unknown>;

        setNetOwner(player: Player, disableMigration: boolean): void;
        resetNetOwner(disableMigration: boolean): void;

        attachTo(target: Entity, otherBoneId: number | string, boneId: number | string, pos: altShared.Vector3, rot: altShared.Vector3, collision: boolean, noFixedRot: boolean): void;
        detach(): void;
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
        pos: altShared.Vector3;
        rot?: altShared.Vector3; // default: { x: 0, y: 0, z: 0 }
        alpha?: number; // default: 255
        textureVariation?: number; // default: 0
        lodDistance?: number; // default: 100
    }

    export abstract class Object extends altShared.Object {
        alpha: number;
        textureVariation: number;
        lodDistance: number;

        activatePhysics(): void;
        placeOnGroundProperly(): void;

        static create(opts: ObjectCreateOptions): Object | null;
    }

    interface PedCreateOptions {
        model: number | string;
        pos: altShared.Vector3;
        heading: number;
    }

    export abstract class Ped extends altShared.Ped {
        health: number;
        maxHealth: number;
        armour: number;
        currentWeapon: number;

        static create(opts: PedCreateOptions): Ped | null;
    }

    export class Player extends altShared.Player {
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

        get currentWeapon(): number;
        set currentWeapon(value: number | string);

        health: number;
        maxHealth: number;
        invincible: boolean;

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

        emit(event: string, ...args: unknown[]): void;
        emitUnreliable(event: string, ...args: unknown[]): void;
        spawn(pos: altShared.Vector3, delay?: number): void;
        despawn(): void;
        setWeaponTintIndex(weaponHash: number | string, tintIndex: number): void;
        addWeaponComponent(weaponHash: number | string, componentHash: number | string): void;
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

        playAnimation(animDict: string, animName: string, blendInSpeed?: number, blendOutSpeed?: number, duration?: number, flag?: number, playbackRate?: number, lockX?: boolean, lockY?: boolean, lockZ?: number): void;
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

        readonly localMeta: Record<string, unknown>;
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
        pos: altShared.Vector3;
        rot?: altShared.Vector3; // default: { x: 0, y: 0, z: 0 }
    }

    export abstract class Vehicle extends altShared.Vehicle {
        readonly neon: altShared.NeonState;

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

        static create(opts: VehicleCreateOptions): Vehicle | null;
    }

    export abstract class VirtualEntity extends altShared.VirtualEntity {
        readonly streamSyncedMeta: Record<string, unknown>;
    }

    export abstract class VirtualEntityGroup extends altShared.VirtualEntityGroup {}

    interface VoiceChannelCreateOptions {
        spatial: boolean;
        maxDistance?: number;
    }

    export abstract class VoiceChannel extends altShared.VoiceChannel {
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

    export abstract class WorldObject extends altShared.WorldObject {
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
        export function emit(eventName: string, ...args: unknown[]): void;

        export function emitPlayers(players: Player[], eventName: string, ...args: unknown[]): void;
        export function emitPlayersUnreliable(players: Player[], eventName: string, ...args: unknown[]): void;

        export function emitAllPlayers(eventName: string, ...args: unknown[]): void;
        export function emitAllPlayersUnreliable(eventName: string, ...args: unknown[]): void;
    }

    export * from "@altv/shared";
}
