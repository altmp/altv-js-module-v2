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
        export const enum PermissionState {
            ALLOWED,
            DENIED,
            UNSPECIFIED,
            FAILED
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
        export const enum BlipSprite {
            Higher,
            Lower,
            PolicePed,
            WantedRadius,
            Area,
            Centre,
            North,
            Waypoint,
            Radius,
            RadiusOutline,
            WeaponHigher,
            WeaponLower,
            HigherAI,
            LowerAI,
            PoliceHeliSpin,
            PolicePlaneMove,
            MPCrew = 27,
            MPFriendlies,
            CableCar = 36,
            Activities,
            Raceflag,
            Safehouse = 40,
            Police,
            PoliceChase,
            PoliceHeli,
            BombA,
            Snitch = 47,
            PlanningLocations,
            CriminalCarsteal = 50,
            CriminalDrugs,
            CriminalHoldups,
            CriminalPlayer = 54,
            CopPatrol = 56,
            CopPlayer,
            CriminalWanted,
            Heist,
            PoliceStation,
            Hospital,
            AssassinsMark,
            Elevator,
            Helicopter,
            RandomCharacter = 66,
            SecurityVan,
            TowTruck,
            IllegalParking = 70,
            Barber,
            CarModShop,
            ClothesStore,
            Tattoo = 75,
            ArmenianFamily,
            LesterFamily,
            MichaelFamily,
            TrevorFamily,
            JewelryHeist,
            DragRaceFinish = 82,
            Rampage = 84,
            VinewoodTours,
            LamarFamily,
            FranklinFamily = 88,
            ChineseStrand,
            FlightSchool,
            EyeSky,
            AirHockey,
            Bar,
            BaseJump,
            Basketball,
            BiolabHeist = 96,
            CabaretClub = 99,
            CarWash,
            ComedyClub = 102,
            Darts,
            DocksHeist,
            FbiHeist,
            FbiOfficersStrand,
            FinaleBankHeist,
            FinancierStrand,
            Golf,
            GunShop,
            InternetCafe,
            MichaelFamilyExile,
            NiceHouseHeist,
            RandomFemale,
            RandomMale,
            RuralBankHeist = 118,
            ShootingRange,
            SolomonStrand,
            StripClub,
            Tennis,
            TrevorFamilyExile,
            MichaelTrevorFamily,
            Triathlon = 126,
            OffRoadRacing,
            GangCops,
            GangMexicans,
            GangBikers,
            SnitchRed = 133,
            CriminalCuffKeys,
            Cinema,
            MusicVenue,
            PoliceStationBlue,
            Airport,
            CriminalSavedVehicle,
            WeedStash,
            Hunting,
            Pool,
            ObjectiveBlue,
            ObjectiveGreen,
            ObjectiveRed,
            ObjectiveYellow,
            ArmsDealing,
            MPFriend,
            CelebrityTheft,
            WeaponAssaultRifle,
            WeaponBat,
            WeaponGrenade,
            WeaponHealth,
            WeaponKnife,
            WeaponMolotov,
            WeaponPistol,
            WeaponRocket,
            WeaponShotgun,
            WeaponSmg,
            WeaponSniper,
            MPNoise,
            PointOfInterest,
            Passive,
            UsingMenu,
            GangCopsPartner = 171,
            WeaponMinigun = 173,
            WeaponArmour = 175,
            PropertyTakeover,
            GangMexicansHighlight,
            GangBikersHighlight,
            TriathlonCycling,
            TriathlonSwimming,
            PropertyTakeoverBikers,
            PropertyTakeoverCops,
            PropertyTakeoverVagos,
            Camera,
            CentreRed,
            HandcuffKeysBikers,
            HandcuffKeysVagos,
            HandcuffsClosedBikers,
            HandcuffsClosedVagos,
            CameraBadger = 192,
            CameraFacade,
            CameraIfruit,
            Yoga = 197,
            Taxi,
            Shrink = 205,
            Epsilon,
            FinancierStrandGrey,
            TrevorFamilyGrey,
            TrevorFamilyRed,
            FranklinFamilyGrey,
            FranklinFamilyBlue,
            FranklinA,
            FranklinB,
            FranklinC,
            GangVehicle = 225,
            GangVehicleBikers,
            GangVehicleCops,
            GangVehicleVagos,
            Guncar,
            DrivingBikers,
            DrivingCops,
            DrivingVagos,
            GangCopsHighlight,
            ShieldBikers,
            ShieldCops = 235,
            ShieldVagos,
            CustodyBikers,
            CustodyVagos,
            ArmsDealingAir = 251,
            PlayerStateArrested,
            PlayerStateCustody,
            PlayerStateDriving,
            PlayerStateKeyholder,
            PlayerStatePartner,
            Ztype = 262,
            Stinger,
            Packer,
            Monroe,
            Fairground,
            Property,
            GangHighlight,
            Altruist,
            AI,
            OnMission,
            CashPickup,
            Chop,
            Dead,
            TerritoryLocked,
            CashLost,
            CashVagos,
            CashCops,
            Hooker,
            Friend,
            Mission2to4,
            Mission2to8,
            Mission2to12,
            Mission2to16,
            CustodyDropOff,
            OnMissionCops,
            OnMissionLost,
            OnMissionVagos,
            CriminalCarStealCops,
            CriminalCarStealBikers,
            CriminalCarStealVagos,
            BandStrand,
            SimeonFamily,
            Mission1,
            Mission2,
            FriendDarts,
            FriendComedyClub,
            FriendCinema,
            FriendTennis,
            FriendStripClub,
            FriendLiveMusic,
            FriendGolf,
            BountyHit,
            UgcMission,
            Horde,
            CrateDrop,
            PlaneDrop,
            Sub,
            Race,
            Deathmatch,
            ArmWrestling,
            Mission1to2,
            ShootingRangeGunShop,
            RaceAir,
            RaceLand,
            RaceSea,
            Tow,
            Garbage,
            Drill,
            Spikes,
            Firetruck,
            Minigun2,
            Bugstar,
            Submarine,
            Chinook,
            GetawayCar,
            MissionBikers1,
            MissionBikers1to2,
            MissionBikers2,
            MissionBikers2to4,
            MissionBikers2to8,
            MissionBikers2to12,
            MissionBikers2to16,
            MissionCops1,
            MissionCops1to2,
            MissionCops2,
            MissionCops2to4,
            MissionCops2to8,
            MissionCops2to12,
            MissionCops2to16,
            MissionVagos1,
            MissionVagos1to2,
            MissionVagos2,
            MissionVagos2to4,
            MissionVagos2to8,
            MissionVagos2to12,
            MissionVagos2to16,
            GangBike,
            GasGrenade,
            PropertyForSale,
            GangAttackPackage,
            MartinMadrazzo,
            EnemyHeliSpin,
            Boost,
            Devin,
            Dock,
            Garage,
            GolfFlag,
            Hangar,
            Helipad,
            JerryCan,
            Mask,
            HeistPrep,
            Incapacitated,
            SpawnPointPickup,
            Boilersuit,
            Completed,
            Rockets,
            GarageForSale,
            HelipadForSale,
            DockForSale,
            HangarForSale,
            Placeholder6,
            Business,
            BusinessForSale,
            RaceBike,
            Parachute,
            TeamDeathmatch,
            RaceFoot,
            VehicleDeathmatch,
            Barry,
            Dom,
            Maryann,
            Cletus,
            Josh,
            Minute,
            Omega,
            Tonya,
            Paparazzo,
            Aim,
            CrateDropBackground,
            GreenAndNetPlayer1,
            GreenAndNetPlayer2,
            GreenAndNetPlayer3,
            GreenAndFriendly,
            NetPlayer1AndNetPlayer2,
            NetPlayer1AndNetPlayer3,
            Creator,
            CreatorDirection,
            Abigail,
            Blimp,
            Repair,
            Testosterone,
            Dinghy,
            Fanatic,
            InfoIcon = 407,
            CaptureTheFlag,
            LastTeamStanding,
            Boat,
            CaptureTheFlagBase,
            CaptureTheFlagOutline = 413,
            CaptureTheFlagBaseNoBag,
            WeaponJerrycan,
            Rp,
            LevelInside,
            BountyHitInside,
            CaptureTheUSAFlag,
            CaptureTheUSAFlagOutline,
            Tank,
            PlayerHeli,
            PlayerPlane,
            PlayerJet,
            CentreStroke,
            PlayerGunCar,
            PlayerBoat,
            MPHeist,
            Temp1,
            Temp2,
            Temp3,
            Temp4,
            Temp5,
            Temp6,
            RaceStunt,
            HotProperty,
            UrbanWarfareVersus,
            KingOfTheCastle,
            PlayerKing,
            DeadDrop,
            PennedIn,
            Beast,
            EdgePointer,
            EdgeCrossTheLine,
            MPLamar,
            Bennys,
            CornerNumber1,
            CornerNumber2,
            CornerNumber3,
            CornerNumber4,
            CornerNumber5,
            CornerNumber6,
            CornerNumber7,
            CornerNumber8,
            Yacht,
            FindersKeepers,
            AssaultPackage,
            HuntTheBoss,
            Sightseer,
            TurretedLimo,
            BellyOfTheBeast,
            YachtLocation,
            PickupBeast,
            PickupZoned,
            PickupRandom,
            PickupSlowTime,
            PickupSwap,
            PickupThermal,
            PickupWeed,
            WeaponRailgun,
            Seashark,
            PickupHidden,
            Warehouse,
            WarehouseForSale,
            Office,
            OfficeForSale,
            Truck,
            Contraband,
            Trailer,
            VIP,
            Cargobob,
            AreaOutline,
            PickupAccelerator,
            PickupGhost,
            PickupDetonator,
            PickupBomb,
            PickupArmoured,
            Stunt,
            WeaponLives,
            StuntPremium,
            Adversary,
            BikerClubhouse,
            BikerCagedIn,
            BikerTurfWar,
            BikerJoust,
            ProductionWeed,
            ProductionCrack,
            ProductionFakeId,
            ProductionMeth,
            ProductionMoney,
            Package,
            Capture1,
            Capture2,
            Capture3,
            Capture4,
            Capture5,
            Capture6,
            Capture7,
            Capture8,
            Capture9,
            Capture10,
            Quad,
            Bus,
            DrugsPackage,
            PickupJump,
            Adversary4,
            Adversary8,
            Adversary10,
            Adversary12,
            Adversary16,
            Laptop,
            PickupDeadline,
            SportsCar,
            WarehouseVehicle,
            RegPapers,
            PoliceStationDropoff,
            Junkyard,
            ExVech1,
            ExVech2,
            ExVech3,
            ExVech4,
            ExVech5,
            ExVech6,
            ExVech7,
            TargetA,
            TargetB,
            TargetC,
            TargetD,
            TargetE,
            TargetF,
            TargetG,
            TargetH,
            Juggernaut,
            PickupRepair,
            SteeringWheel,
            Trophy,
            PickupRocketBoost,
            PickupHomingRocket,
            PickupMachinegun,
            PickupParachute,
            PickupTime5,
            PickupTime10,
            PickupTime15,
            PickupTime20,
            PickupTime30,
            Supplies,
            PropertyBunker,
            GrWvm1,
            GrWvm2,
            GrWvm3,
            GrWvm4,
            GrWvm5,
            GrWvm6,
            GrCovertOps,
            AdversaryBunker,
            GrMocUpgrade,
            GrWUpgrade,
            SmCargo,
            SmHangar,
            TfCheckpoint,
            RaceTf,
            SmWp1,
            SmWp2,
            SmWp3,
            SmWp4,
            SmWp5,
            SmWp6,
            SmWp7,
            SmWp8,
            SmWp9,
            SmWp10,
            SmWp11,
            SmWp12,
            SmWp13,
            SmWp14,
            NhpBag,
            NhpChest,
            NhpOrbit,
            NhpVeh1,
            NhpBase,
            NhpOverlay,
            NhpTurret,
            NhpMgFirewall,
            NhpMgNode,
            NhpWp1,
            NhpWp2,
            NhpWp3,
            NhpWp4,
            NhpWp5,
            NhpWp6,
            NhpWp7,
            NhpWp8,
            NhpWp9,
            NhpCCTV,
            NhpStarterpack,
            NhpTurretConsole,
            NhpMgMirRotate,
            NhpMgMirStatic,
            NhpMgProxy,
            AcsrRaceTarget,
            AcsrRaceHotring,
            AcsrWp1,
            AcsrWp2,
            BatClubProperty,
            BatCargo,
            BatTruck,
            BatHackJewel,
            BatHackGold,
            BatKeypad,
            BatHackTarget,
            PickupDtbHealth,
            PickupDtbBlastIncrease,
            PickupDtbBlastDecrease,
            PickupDtbBombIncrease,
            PickupDtbBombDecrease,
            BatRivalClub,
            BatDrone,
            BatCashReg,
            CCTV,
            BatAssassinate,
            BatPbus,
            BatWp1,
            BatWp2,
            BatWp3,
            BatWp4,
            BatWp5,
            BatWp6,
            Blimp2,
            Oppressor2,
            BatWp7,
            ArenaSeries,
            ArenaPremium,
            ArenaWorkshop,
            RaceWars,
            ArenaTurret,
            ArenaRCCar,
            ArenaRCWorkshop,
            ArenaTrapFire,
            ArenaTrapFlip,
            ArenaTrapSea,
            ArenaTrapTurn,
            ArenaTrapPit,
            ArenaTrapMine,
            ArenaTrapBomb,
            ArenaTrapWall,
            ArenaTrapBrd,
            ArenaTrapSbrd,
            ArenaBruiser,
            ArenaBrutus,
            ArenaCerberus,
            ArenaDeathbike,
            ArenaDominator,
            ArenaImpaler,
            ArenaImperator,
            ArenaIssi,
            ArenaSasquatch,
            ArenaScarab,
            ArenaSlamvan,
            ArenaZr,
        }
        export const enum BlipColor {
            White,
            Red,
            Green,
            Blue,
            Yellow = 5,
            LightRed,
            Violet,
            Pink,
            LightOrange,
            LightBrown,
            LightGreen,
            LightBlue,
            LightPurple,
            DarkPurple,
            Cyan,
            LightYellow,
            Organe,
            DarkPink = 19,
            GraniteGreen,
            DarkBrown,
            LightGray,
            LightPink,
            LemonGreen,
            ForestGreen,
            ElectricBlue,
            BrightPurple,
            DarkYellow,
            DarkCyan = 30,
            Beige = 36,
            DarkGray = 40,
            PinkRed,
            Gold = 46,
            Orange,
            BrilliantRose,
            MediumPurple = 50,
            Salmon,
            DarkGreen,
            BlizzardBlue,
            OracleBlue,
            Silver,
            EastBay = 58,
            YellowOrange = 60,
            MulberryPink,
            AltoGray,
            JellyBeanBlue,
            DarkOrange,
            Mamba,
            TransparentBlack = 72,
            DeepRed = 76,
            TransparentRed = 79,
            TransparentBlue = 80,
            Purple = 83,
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
        export const enum CheckpointType {
            CylinderSingleArrow,
            CylinderDoubleArrow,
            CylinderTripleArrow,
            CylinderCycleArrow,
            CylinderCheckerboard,
            CylinderWrench,
            CylinderSingleArrow2,
            CylinderDoubleArrow2,
            CylinderTripleArrow2,
            CylinderCycleArrow2,
            CylinderCheckerboard2,
            CylinderWrench2,
            RingSingleArrow,
            RingDoubleArrow,
            RingTripleArrow,
            RingCycleArrow,
            RingCheckerboard,
            SingleArrow,
            DoubleArrow,
            TripleArrow,
            CycleArrow,
            Checkerboard,
            CylinderSingleArrow3,
            CylinderDoubleArrow3,
            CylinderTripleArrow3,
            CylinderCycleArrow3,
            CylinderCheckerboard3,
            CylinderSingleArrow4,
            CylinderDoubleArrow4,
            CylinderTripleArrow4,
            CylinderCycleArrow4,
            CylinderCheckerboard4,
            CylinderSingleArrow5,
            CylinderDoubleArrow5,
            CylinderTripleArrow5,
            CylinderCycleArrow5,
            CylinderCheckerboard5,
            RingPlaneUp,
            RingPlaneLeft,
            RingPlaneRight,
            RingPlaneDown,
            Empty,
            Ring,
            Empty2,
            Cylinder,
            Cylinder1,
            Cylinder2,
            Cylinder3,
            Cylinder4,
            Cylinder5,
            Empty3,
            Empty4,
            Empty5,
            Empty6,
            RingDollar,
            RingWolf,
            RingQuestionMark,
            RingPlane,
            RingChopper,
            RingBoat,
            RingCar,
            RingBike,
            RingBicycle,
            RingTruck,
            RingParachute,
            RingJetpack,
            RingWhirl,
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
        export const enum VehicleLockState {
            None,
            Unlocked,
            Locked,
            LockoutPlayerOnly,
            LockPlayerInside,
            InitiallyLocked,
            ForceDoorsShut,
            LockedCanBeDamaged,
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
        export const enum MarkerType {
            MarkerCone = 0,
            MarkerCylinder = 1,
            MarkerArrow = 2,
            MarkerArrowFlat = 3,
            MarkerFlag = 4,
            MarkerRingFlag = 5,
            MarkerRing = 6,
            MarkerPlane = 7,
            MarkerBikeLogo1 = 8,
            MarkerBikeLogo2 = 9,
            MarkerNum0 = 10,
            MarkerNum1 = 11,
            MarkerNum2 = 12,
            MarkerNum3 = 13,
            MarkerNum4 = 14,
            MarkerNum5 = 15,
            MarkerNum6 = 16,
            MarkerNum7 = 17,
            MarkerNum8 = 18,
            MarkerNum9 = 19,
            MarkerChevron1 = 20,
            MarkerChevron2 = 21,
            MarkerChevron3 = 22,
            MarkerRingFlat = 23,
            MarkerLap = 24,
            MarkerHalo = 25,
            MarkerHaloPoint = 26,
            MarkerHaloRotate = 27,
            MarkerSphere = 28,
            MarkerMoney = 29,
            MarkerLines = 30,
            MarkerBeast = 31,
            MarkerQuestionMark = 32,
            MarkerTransformPlane = 33,
            MarkerTransformHelicopter = 34,
            MarkerTransformBoat = 35,
            MarkerTransformCar = 36,
            MarkerTransformBike = 37,
            MarkerTransformPushBike = 38,
            MarkerTransformTruck = 39,
            MarkerTransformParachute = 40,
            MarkerTransformThruster = 41,
            MarkerWarp = 42,
            MarkerBoxes = 43,
            MarkerPitLane = 44,
        }
        export const enum AudioCategory {
            x44E21C90 = "0x44E21C90",
            xBAD598C7 = "0xBAD598C7",
            xA4D158B0 = "0xA4D158B0",
            FrontendMenu = "frontend_menu",
            Cutscenes = "cutscenes",
            GameWorld = "game_world",
            Ambience = "ambience",
            Weapons = "weapons",
            Peds = "peds",
            Speech = "speech",
            Vehicles = "vehicles",
            Collisions = "collisions",
            HUD = "hud",
            WeaponsExplosions = "weapons_explosions",
            WeaponsGuns = "weapons_guns",
            x4E8BCAED = "0x4E8BCAED",
            x32157574 = "0x32157574",
            PedsClothing = "peds_clothing",
            PedsCollisions = "peds_collisions",
            xF7C35252 = "0xF7C35252",
            VehiclesHelis = "vehicles_helis",
            VehiclesWheels = "vehicles_wheels",
            VehiclesWheelsSkids = "vehicles_wheels_skids",
            x2EED1D0A = "0x2EED1D0A",
            VehiclesHorns = "vehicles_horns",
            VehiclesHornsLoud = "vehicles_horns_loud",
            VehiclesSirens = "vehicles_sirens",
            VehiclesDoors = "vehicles_doors",
            VehiclesBrakes = "vehicles_brakes",
            VehiclesChassisRattle = "vehicles_chassis_rattle",
            VehiclesSuspension = "vehicles_suspension",
            xDF9CFFD4 = "0xDF9CFFD4",
            VehiclesEnginesIntake = "vehicles_engines_intake",
            xF48DE3B3 = "0xF48DE3B3",
            VehiclesEnginesDamage = "vehicles_engines_damage",
            VehiclesEnginesIgnition = "vehicles_engines_ignition",
            xB607457F = "0xB607457F",
            x39736A51 = "0x39736A51",
            x3F6594E4 = "0x3F6594E4",
            xE86DF43F = "0xE86DF43F",
            x1C507071 = "0x1C507071",
            Music = "music",
            MusicLoading = "music_loading",
            x6244F855 = "0x6244F855",
            xD59675EA = "0xD59675EA",
            xEA185B02 = "0xEA185B02",
            xAC3F546D = "0xAC3F546D",
            x41ACDDFF = "0x41ACDDFF",
            xC8B2D787 = "0xC8B2D787",
            x3AA35DEF = "0x3AA35DEF",
            xDCA3CC61 = "0xDCA3CC61",
            x1F418253 = "0x1F418253",
            x933E72C3 = "0x933E72C3",
            xF05AAEDD = "0xF05AAEDD",
            xC4872161 = "0xC4872161",
            xAA0678B2 = "0xAA0678B2",
            VehiclesEnginesCooling = "vehicles_engines_cooling",
            Scripted = "scripted",
            AmbienceWeather = "ambience_weather",
            x6F56A5DC = "0x6F56A5DC",
            VehiclesBoatsEngines = "vehicles_boats_engines",
            AmbienceInsects = "ambience_insects",
            AmbienceBirds = "ambience_birds",
            Radio = "radio",
            x52BA33D4 = "0x52BA33D4",
            x45EB536F = "0x45EB536F",
            FrontendRadio = "frontend_radio",
            x9B60B77E = "0x9B60B77E",
            x044986F4 = "0x044986F4",
            xF7954E76 = "0xF7954E76",
            CollisionsVehiclesGlass = "collisions_vehicles_glass",
            xEB0390D7 = "0xEB0390D7",
            x80722AAA = "0x80722AAA",
            Fire = "fire",
            Water = "water",
            Score = "score",
            Doors = "doors",
            x01E27C7E = "0x01E27C7E",
            xA95BF404 = "0xA95BF404",
            InteractiveMusic = "interactive_music",
            x9205C7A1 = "0x9205C7A1",
            xD3594A47 = "0xD3594A47",
            x20230050 = "0x20230050",
            xEA1277B9 = "0xEA1277B9",
            xF4908CAD = "0xF4908CAD",
            x05D22F30 = "0x05D22F30",
            x11034592 = "0x11034592",
            x1E51E02F = "0x1E51E02F",
            x6D867E97 = "0x6D867E97",
            x9C6A4771 = "0x9C6A4771",
            x6C742462 = "0x6C742462",
            AnimalsFootsteps = "animals_footsteps",
            x414231B5 = "0x414231B5",
            Melee = "melee",
            x992F6CB7 = "0x992F6CB7",
            x75FB2B65 = "0x75FB2B65",
            x368CC071 = "0x368CC071",
            xB2681B31 = "0xB2681B31",
            xB4C14B9C = "0xB4C14B9C",
            xE3FAF7D3 = "0xE3FAF7D3",
            xCD3365DE = "0xCD3365DE",
            x864AAAB9 = "0x864AAAB9",
            Weather = "weather",
            WeatherWind = "weather_wind",
            x4FFD9CA5 = "0x4FFD9CA5",
            xCB2382B4 = "0xCB2382B4",
            xBCE6F3E0 = "0xBCE6F3E0",
            x781669E6 = "0x781669E6",
            WeatherRain = "weather_rain",
            VehiclesTrain = "vehicles_train",
            xF1754C85 = "0xF1754C85",
            CollisionsCloth = "collisions_cloth",
            VehiclesPlanes = "vehicles_planes",
            VehiclesPlanesJet = "vehicles_planes_jet",
            xF4FABC2A = "0xF4FABC2A",
            x3EB27392 = "0x3EB27392",
            CollisionsLouder = "collisions_louder",
            xED39E59D = "0xED39E59D",
            x011F1827 = "0x011F1827",
            AmbienceMusic = "ambience_music",
            x85B8BFD4 = "0x85B8BFD4",
            xB421C2DC = "0xB421C2DC",
            VehiclesBoatsWater = "vehicles_boats_water",
            WaterSwimming = "water_swimming",
            x31A9A815 = "0x31A9A815",
            x3874EB6C = "0x3874EB6C",
            x85DBC375 = "0x85DBC375",
            xC7D71D61 = "0xC7D71D61",
            x2F34D6FC = "0x2F34D6FC",
            ScriptedAlarms = "scripted_alarms",
            WeatherRainHeavy = "weather_rain_heavy",
            x88EEAE72 = "0x88EEAE72",
            VehiclesHelisDistant = "vehicles_helis_distant",
            VehiclesPlanesProp = "vehicles_planes_prop",
            VehiclesPlanesClose = "vehicles_planes_close",
            xBC11E471 = "0xBC11E471",
            WaterOcean = "water_ocean",
            x25E385A7 = "0x25E385A7",
            VehiclesPlanesDistant = "vehicles_planes_distant",
            VehiclesEnginesStartup = "vehicles_engines_startup",
            xC701057A = "0xC701057A",
            FireLouder = "fire_louder",
            x0E212957 = "0x0E212957",
            Underwater = "underwater",
            VehiclesTrainCarriage = "vehicles_train_carriage",
            VehiclesTrainClack = "vehicles_train_clack",
            PedsWind = "peds_wind",
            VehiclesExtrasLoud = "vehicles_extras_loud",
            VehiclesWheelsLoud = "vehicles_wheels_loud",
            AmbienceIndustrial = "ambience_industrial",
            AmbienceSpeech = "ambience_speech",
            xF0E66096 = "0xF0E66096",
            x3A52AFA3 = "0x3A52AFA3",
            WaterRiver = "water_river",
            WeatherThunder = "weather_thunder",
            VehiclesBicycles = "vehicles_bicycles",
            VehiclesBicyclesMechanical = "vehicles_bicycles_mechanical",
            AmbienceGeneral = "ambience_general",
            AmbienceCollectables = "ambience_collectables",
            UnderwaterLoud = "underwater_loud",
            SpeechAmbient = "speech_ambient",
            SpeechScripted = "speech_scripted",
            SpeechPain = "speech_pain",
            SpeechBreathing = "speech_breathing",
            xBF162C33 = "0xBF162C33",
            xB9CB44C7 = "0xB9CB44C7",
            xDA38F55D = "0xDA38F55D",
            CollisionsGlass = "collisions_glass",
            WaterLoud = "water_loud",
            xF846B110 = "0xF846B110",
            x0D3C9D38 = "0x0D3C9D38",
            VehiclesTrainBrakes = "vehicles_train_brakes",
            xD2626419 = "0xD2626419",
            WeaponsExplosionsLoud = "weapons_explosions_loud",
            PedsCollisionsLoud = "peds_collisions_loud",
            x03D39751 = "0x03D39751",
            CollisionsScripted = "collisions_scripted",
            xE8C16DEA = "0xE8C16DEA",
            FrontendMenuLoud = "frontend_menu_loud",
            WeatherWindFoliage = "weather_wind_foliage",
            VehiclesPlanesExtras = "vehicles_planes_extras",
            x0BE5A8C0 = "0x0BE5A8C0",
            VehiclesCarBy = "vehicles_car_by",
            ScriptedTV = "scripted_tv",
            x02C7B342 = "0x02C7B342",
            x2BA33BE9 = "0x2BA33BE9",
            x9748F077 = "0x9748F077",
            DoorsLoud = "doors_loud",
            x0607FDB8 = "0x0607FDB8",
            ScriptedLouder = "scripted_louder",
            xA6A84701 = "0xA6A84701",
            x3C496EED = "0x3C496EED",
            VehiclesEnginesReflections = "vehicles_engines_reflections",
            WeatherRainProps = "weather_rain_props",
            UnderwaterSwimming = "underwater_swimming",
            x1FF21B89 = "0x1FF21B89",
            xA6DA13DC = "0xA6DA13DC",
            VehiclesEnginesLoud = "vehicles_engines_loud",
            x6A3DD9A1 = "0x6A3DD9A1",
            x53B27328 = "0x53B27328",
            UnderwaterMuted = "underwater_muted",
            x6805AAC2 = "0x6805AAC2",
            x8A91FE75 = "0x8A91FE75",
            xEB0865AB = "0xEB0865AB",
            xF3196F77 = "0xF3196F77",
            x05403EE1 = "0x05403EE1",
            x63614939 = "0x63614939",
            xBC72B5EB = "0xBC72B5EB",
            FrontendGameLoud = "frontend_game_loud",
            xF2C3426E = "0xF2C3426E",
            x639A44A4 = "0x639A44A4",
            x266E012E = "0x266E012E",
            xACA58232 = "0xACA58232",
            x7A6F1418 = "0x7A6F1418",
            xD4AE89CA = "0xD4AE89CA",
            xFDB42EDF = "0xFDB42EDF",
            xFF7A0598 = "0xFF7A0598",
            x5A6165D9 = "0x5A6165D9",
            x585863F0 = "0x585863F0",
            x0E4CF672 = "0x0E4CF672",
            x11D52176 = "0x11D52176",
            xF841C9F9 = "0xF841C9F9",
            x291E7FD7 = "0x291E7FD7",
            x94821026 = "0x94821026",
            xFB40B82B = "0xFB40B82B",
            xCFF0C1C2 = "0xCFF0C1C2",
        }
        export const enum FileEncoding {
            Utf8 = "utf-8",
            Utf16 = "utf-16",
            Binary = "binary",
        }
        export const enum ModelType {
            Invalid,
            Ped,
            Automobile,
            Plane,
            Trailer,
            QuadBike,
            SubmarineCar,
            AmphibiousAutomobile,
            AmphibiousQuadBike,
            Heli,
            Blimp,
            Autogyro,
            Bike,
            Bmx,
            Boat,
            Train,
            Submarine,
            Object,
        }
        export const enum KeyCode {
            Key0 = 48,
            Key1 = 49,
            Key2 = 50,
            Key3 = 51,
            Key4 = 52,
            Key5 = 53,
            Key6 = 54,
            Key7 = 55,
            Key8 = 56,
            Key9 = 57,
            Backspace = 8,
            Tab = 9,
            Clear = 12,
            Enter = 13,
            Return = 13,
            Escape = 27,
            Space = 32,
            Left = 37,
            Up = 38,
            Right = 39,
            Down = 40,
            Delete = 46,
            Insert = 45,
            Home = 36,
            End = 35,
            PageUp = 33,
            PageDown = 34,
            CapsLock = 20,
            Shift = 16,
            Alt = 18,
            Ctrl = 17,
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
            KpMultiply = 106,
            KpAdd = 107,
            KpSubtract = 109,
            KpDecimal = 110,
            KpDivide = 111,
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
            Numpad0 = 96,
            Numpad1 = 97,
            Numpad2 = 98,
            Numpad3 = 99,
            Numpad4 = 100,
            Numpad5 = 101,
            Numpad6 = 102,
            Numpad7 = 103,
            Numpad8 = 104,
            Numpad9 = 105,
            MouseLeft = 1,
            MouseRight = 2,
            MouseMiddle = 4,
        }
        export const enum PedConfigFlag {
            NoCriticalHits = 2,
            DrownsInWater = 3,
            DisableReticuleFixedLockon = 4,
            UpperBodyDamageAnimsOnly = 7,
            NeverLeavesGroup = 13,
            BlockNonTemporaryEvents = 17,
            CanPunch = 18,
            IgnoreSeenMelee = 24,
            GetOutUndriveableVehicle = 29,
            CanFlyThruWindscreen = 32,
            DiesWhenRagdoll = 33,
            HasHelmet = 34,
            PutOnMotorcycleHelmet = 35,
            DontTakeOffHelmet = 36,
            DisableEvasiveDives = 39,
            DontInfluenceWantedLevel = 42,
            DisablePlayerLockon = 43,
            DisableLockonToRandomPeds = 44,
            AllowLockonToFriendlyPlayers = 45,
            BeingDeleted = 47,
            BlockWeaponSwitching = 48,
            NoCollision = 52,
            IsShooting = 58,
            WasShooting = 59,
            IsOnGround = 60,
            WasOnGround = 61,
            InVehicle = 62,
            OnMount = 63,
            AttachedToVehicle = 64,
            IsSwimming = 65,
            WasSwimming = 66,
            IsSkiing = 67,
            IsSitting = 68,
            KilledByStealth = 69,
            KilledByTakedown = 70,
            Knockedout = 71,
            IsSniperScopeActive = 72,
            SuperDead = 73,
            UsingCoverPoint = 75,
            IsInTheAir = 76,
            IsAimingGun = 78,
            ForcePedLoadCover = 93,
            VaultFromCover = 97,
            IsDrunk = 100,
            ForcedAim = 101,
            IsNotRagdollAndNotPlayingAnim = 104,
            ForceReload = 105,
            DontActivateRagdollFromVehicleImpact = 106,
            DontActivateRagdollFromBulletImpact = 107,
            DontActivateRagdollFromExplosions = 108,
            DontActivateRagdollFromFire = 109,
            DontActivateRagdollFromElectrocution = 110,
            KeepWeaponHolsteredUnlessFired = 113,
            GetOutBurningVehicle = 116,
            BumpedByPlayer = 117,
            RunFromFiresAndExplosions = 118,
            TreatAsPlayerDuringTargeting = 119,
            IsHandCuffed = 120,
            IsAnkleCuffed = 121,
            DisableMelee = 122,
            DisableUnarmedDrivebys = 123,
            JustGetsPulledOutWhenElectrocuted = 124,
            NmMessage466 = 125,
            WillNotHotwireLawEnforcementVehicle = 126,
            WillCommandeerRatherThanJack = 127,
            CanBeAgitated = 128,
            ForcePedToFaceLeftInCover = 129,
            ForcePedToFaceRightInCover = 130,
            BlockPedFromTurningInCover = 131,
            KeepRelationshipGroupAfterCleanUp = 132,
            ForcePedToBeDragged = 133,
            PreventPedFromReactingToBeingJacked = 134,
            IsScuba = 135,
            WillArrestRatherThanJack = 136,
            RemoveDeadExtraFarAway = 137,
            RidingTrain = 138,
            ArrestResult = 139,
            CanAttackFriendly = 140,
            WillJackAnyPlayer = 141,
            WillJackWantedPlayersRatherThanStealCar = 144,
            ShootingAnimFlag = 145,
            DisableLadderClimbing = 146,
            StairsDetected = 147,
            SlopeDetected = 148,
            CowerInsteadOfFlee = 150,
            CanActivateRagdollWhenVehicleUpsideDown = 151,
            AlwaysRespondToCriesForHelp = 152,
            DisableBloodPoolCreation = 153,
            ShouldFixIfNoCollision = 154,
            CanPerformArrest = 155,
            CanPerformUncuff = 156,
            CanBeArrested = 157,
            PlayerPreferFrontSeatMP = 159,
            IsInjured = 166,
            DontEnterVehiclesInPlayersGroup = 167,
            PreventAllMeleeTaunts = 169,
            IsInjured2 = 170,
            AlwaysSeeApproachingVehicles = 171,
            CanDiveAwayFromApproachingVehicles = 172,
            AllowPlayerToInterruptVehicleEntryExit = 173,
            OnlyAttackLawIfPlayerIsWanted = 174,
            PedsJackingMeDontGetIn = 177,
            PedIgnoresAnimInterruptEvents = 179,
            IsInCustody = 180,
            ForceStandardBumpReactionThresholds = 181,
            LawWillOnlyAttackIfPlayerIsWanted = 182,
            IsAgitated = 183,
            PreventAutoShuffleToDriversSeat = 184,
            UseKinematicModeWhenStationary = 185,
            EnableWeaponBlocking = 186,
            HasHurtStarted = 187,
            DisableHurt = 188,
            PlayerIsWeird = 189,
            DoNothingWhenOnFootByDefault = 193,
            UsingScenario = 194,
            VisibleOnScreen = 195,
            DontActivateRagdollOnVehicleCollisionWhenDead = 199,
            HasBeenInArmedCombat = 200,
            AvoidanceIgnoreAll = 202,
            AvoidanceIgnoredByAll = 203,
            AvoidanceIgnoreGroup1 = 204,
            AvoidanceMemberOfGroup1 = 205,
            ForcedToUseSpecificGroupSeatIndex = 206,
            DisableExplosionReactions = 208,
            DodgedPlayer = 209,
            WaitingForPlayerControlInterrupt = 210,
            ForcedToStayInCover = 211,
            GeneratesSoundEvents = 212,
            ListensToSoundEvents = 213,
            AllowToBeTargetedInAVehicle = 214,
            WaitForDirectEntryPointToBeFreeWhenExiting = 215,
            OnlyRequireOnePressToExitVehicle = 216,
            ForceExitToSkyDive = 217,
            DontEnterLeadersVehicle = 220,
            DisableExitToSkyDive = 221,
            Shrink = 223,
            MeleeCombat = 224,
            DisablePotentialToBeWalkedIntoResponse = 225,
            DisablePedAvoidance = 226,
            ForceRagdollUponDeath = 227,
            DisablePanicInVehicle = 229,
            AllowedToDetachTrailer = 230,
            IsHoldingProp = 236,
            BlocksPathingWhenDead = 237,
            ForceSkinCharacterCloth = 240,
            DisableStoppingVehicleEngine = 241,
            PhoneDisableTextingAnimations = 242,
            PhoneDisableTalkingAnimations = 243,
            PhoneDisableCameraAnimations = 244,
            DisableBlindFiringInShotReactions = 245,
            AllowNearbyCoverUsage = 246,
            CanPlayInCarIdles = 248,
            CanAttackNonWantedPlayerAsLaw = 249,
            WillTakeDamageWhenVehicleCrashes = 250,
            AICanDrivePlayerAsRearPassenger = 251,
            PlayerCanJackFriendlyPlayers = 252,
            IsOnStairs = 253,
            AIDriverAllowFriendlyPassengerSeatEntry = 255,
            AllowMissionPedToUseInjuredMovement = 257,
            PreventUsingLowerPrioritySeats = 261,
            DisableClosingVehicleDoor = 264,
            TeleportToLeaderVehicle = 268,
            AvoidanceIgnoreWeirdPedBuffer = 269,
            OnStairSlope = 270,
            DontBlipCop = 272,
            ClimbedShiftedFence = 273,
            KillWhenTrapped = 275,
            EdgeDetected = 276,
            AvoidTearGas = 279,
            NoWrithe = 281,
            OnlyUseForcedSeatWhenEnteringHeliInGroup = 282,
            DisableWeirdPedEvents = 285,
            ShouldChargeNow = 286,
            RagdollingOnBoat = 287,
            HasBrandishedWeapon = 288,
            FreezePosition = 292,
            DisableShockingEvents = 294,
            NeverReactToPedOnRoof = 296,
            DisableShockingDrivingOnPavementEvents = 299,
            DisablePedConstraints = 301,
            ForceInitialPeekInCover = 302,
            DisableJumpingFromVehiclesAfterLeader = 305,
            IsInCluster = 310,
            ShoutToGroupOnPlayerMelee = 311,
            IgnoredByAutoOpenDoors = 312,
            NoPedMelee = 314,
            CheckLoSForSoundEvents = 315,
            CanSayFollowedByPlayerAudio = 317,
            ActivateRagdollFromMinorPlayerContact = 318,
            ForcePoseCharacterCloth = 320,
            HasClothCollisionBounds = 321,
            HasHighHeels = 322,
            DontBehaveLikeLaw = 324,
            DisablePoliceInvestigatingBody = 326,
            DisableWritheShootFromGround = 327,
            LowerPriorityOfWarpSeats = 328,
            DisableTalkTo = 329,
            DontBlip = 330,
            IsSwitchingWeapon = 331,
            IgnoreLegIkRestrictions = 332,
            AllowTaskDoNothingTimeslicing = 339,
            NotAllowedToJackAnyPlayers = 342,
            AlwaysLeaveTrainUponArrival = 345,
            OnlyWritheFromWeaponDamage = 347,
            UseSloMoBloodVfx = 348,
            EquipJetpack = 349,
            PreventDraggedOutOfCarThreatResponse = 350,
            ForceDeepSurfaceCheck = 356,
            DisableDeepSurfaceAnims = 357,
            DontBlipNotSynced = 358,
            IsDuckingInVehicle = 359,
            PreventAutoShuffleToTurretSeat = 360,
            DisableEventInteriorStatusCheck = 361,
            HasReserveParachute = 362,
            UseReserveParachute = 363,
            TreatDislikeAsHateWhenInCombat = 364,
            OnlyUpdateTargetWantedIfSeen = 365,
            AllowAutoShuffleToDriversSeat = 366,
            PreventReactingToSilencedCloneBullets = 372,
            DisableInjuredCryForHelpEvents = 373,
            NeverLeaveTrain = 374,
            DontDropJetpackOnDeath = 375,
            DisableAutoEquipHelmetsInBikes = 380,
            IsClimbingLadder = 388,
            HasBareFeet = 389,
            GoOnWithoutVehicleIfItIsUnableToGetBackToRoad = 391,
            BlockDroppingHealthSnacksOnDeath = 392,
            ForceThreatResponseToNonFriendToFriendMeleeActions = 394,
            DontRespondToRandomPedsDamage = 395,
            AllowContinuousThreatResponseWantedLevelUpdates = 396,
            KeepTargetLossResponseOnCleanup = 397,
            PlayersDontDragMeOutOfCar = 398,
            BroadcastRepondedToThreatWhenGoingToPointShooting = 399,
            IgnorePedTypeForIsFriendlyWith = 400,
            TreatNonFriendlyAsHateWhenInCombat = 401,
            DontLeaveVehicleIfLeaderNotInVehicle = 402,
            AllowMeleeReactionIfMeleeProofIsOn = 404,
            UseNormalExplosionDamageWhenBlownUpInVehicle = 407,
            DisableHomingMissileLockForVehiclePedInside = 408,
            DisableTakeOffScubaGear = 409,
            Alpha = 410,
            LawPedsCanFleeFromNonWantedPlayer = 411,
            ForceBlipSecurityPedsIfPlayerIsWanted = 412,
            IsHolsteringWeapon = 413,
            UseGoToPointForScenarioNavigation = 414,
            DontClearLocalPassengersWantedLevel = 415,
            BlockAutoSwapOnWeaponPickups = 416,
            ThisPedIsATargetPriorityForAI = 417,
            IsSwitchingHelmetVisor = 418,
            ForceHelmetVisorSwitch = 419,
            FlamingFootprints = 421,
            DisableVehicleCombat = 422,
            DisablePropKnockOff = 423,
            FallsLikeAircraft = 424,
            UseLockpickVehicleEntryAnimations = 426,
            IgnoreInteriorCheckForSprinting = 427,
            SwatHeliSpawnWithinLastSpottedLocation = 428,
            DisableStartingVehicleEngine = 429,
            IgnoreBeingOnFire = 430,
            DisableTurretOrRearSeatPreference = 431,
            DisableWantedHelicopterSpawning = 432,
            UseTargetPerceptionForCreatingAimedAtEvents = 433,
            DisableHomingMissileLockon = 434,
            ForceIgnoreMaxMeleeActiveSupportCombatants = 435,
            StayInDefensiveAreaWhenInVehicle = 436,
            DontShoutTargetPosition = 437,
            DisableHelmetArmor = 438,
            PreventVehExitDueToInvalidWeapon = 441,
            IgnoreNetSessionFriendlyFireCheckForAllowDamage = 442,
            DontLeaveCombatIfTargetPlayerIsAttackedByPolice = 443,
            CheckLockedBeforeWarp = 444,
            DontShuffleInVehicleToMakeRoom = 445,
            GiveWeaponOnGetup = 446,
            DontHitVehicleWithProjectiles = 447,
            DisableForcedEntryForOpenVehiclesFromTryLockedDoor = 448,
            FiresDummyRockets = 449,
            IsArresting = 450,
            IsDecoyPed = 451,
            HasEstablishedDecoy = 452,
            BlockDispatchedHelicoptersFromLanding = 453,
            DontCryForHelpOnStun = 454,
            CanBeIncapacitated = 456,
            MutableForcedAim = 457,
            DontChangeTargetFromMelee = 458,
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

        interface ScriptEventContext extends EventContext {
            readonly eventName: string;
            readonly args: any[];
        }
        interface ClientScriptEventContext extends ScriptEventContext {
            readonly player: Player | undefined;
        }
        interface ServerEventContext extends ScriptEventContext {}
        interface ConsoleCommandEventContext extends EventContext {
            readonly name: string;
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

        export function on(eventName: string, callback: (context: { args: any[] }) => void): void;
        export function onRemote(eventName: string, callback: (context: { args: any[], player: Player | undefined }) => void): void;

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

    export class WorldObject {
    }

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
        get isAiming(): boolean;
        get isShooting(): boolean;
        get isReloading(): boolean;
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

    export interface ColShape extends WorldObject {
    }

    export class ColShape {
    }

    export interface Checkpoint extends ColShape {
    }

    export class Checkpoint {
    }

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
