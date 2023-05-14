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
            MARKER_CONE = 0,
            MARKER_CYLINDER = 1,
            MARKER_ARROW = 2,
            MARKER_ARROW_FLAT = 3,
            MARKER_FLAG = 4,
            MARKER_RING_FLAG = 5,
            MARKER_RING = 6,
            MARKER_PLANE = 7,
            MARKER_BIKE_LOGO1 = 8,
            MARKER_BIKE_LOGO2 = 9,
            MARKER_NUM0 = 10,
            MARKER_NUM1 = 11,
            MARKER_NUM2 = 12,
            MARKER_NUM3 = 13,
            MARKER_NUM4 = 14,
            MARKER_NUM5 = 15,
            MARKER_NUM6 = 16,
            MARKER_NUM7 = 17,
            MARKER_NUM8 = 18,
            MARKER_NUM9 = 19,
            MARKER_CHEVRON1 = 20,
            MARKER_CHEVRON2 = 21,
            MARKER_CHEVRON3 = 22,
            MARKER_RING_FLAT = 23,
            MARKER_LAP = 24,
            MARKER_HALO = 25,
            MARKER_HALO_POINT = 26,
            MARKER_HALO_ROTATE = 27,
            MARKER_SPHERE = 28,
            MARKER_MONEY = 29,
            MARKER_LINES = 30,
            MARKER_BEAST = 31,
            MARKER_QUESTION_MARK = 32,
            MARKER_TRANSFORM_PLANE = 33,
            MARKER_TRANSFORM_HELICOPTER = 34,
            MARKER_TRANSFORM_BOAT = 35,
            MARKER_TRANSFORM_CAR = 36,
            MARKER_TRANSFORM_BIKE = 37,
            MARKER_TRANSFORM_PUSH_BIKE = 38,
            MARKER_TRANSFORM_TRUCK = 39,
            MARKER_TRANSFORM_PARACHUTE = 40,
            MARKER_TRANSFORM_THRUSTER = 41,
            MARKER_WARP = 42,
            MARKER_BOXES = 43,
            MARKER_PIT_LANE = 44,
        }
        export const enum AudioCategory {
            AMBIENCE = "ambience",
            AMBIENCE_BIRDS = "ambience_birds",
            AMBIENCE_COLLECTABLES = "ambience_collectables",
            AMBIENCE_GENERAL = "ambience_general",
            AMBIENCE_INDUSTRIAL = "ambience_industrial",
            AMBIENCE_INSECTS = "ambience_insects",
            AMBIENCE_MUSIC = "ambience_music",
            AMBIENCE_SPEECH = "ambience_speech",
            AMBIENCE_WEATHER = "ambience_weather",
            ANIMALS_FOOTSTEPS = "animals_footsteps",
            COLLISIONS = "collisions",
            COLLISIONS_CLOTH = "collisions_cloth",
            COLLISIONS_GLASS = "collisions_glass",
            COLLISIONS_LOUDER = "collisions_louder",
            COLLISIONS_SCRIPTED = "collisions_scripted",
            COLLISIONS_VEHICLES_GLASS = "collisions_vehicles_glass",
            CUTSCENES = "cutscenes",
            DOORS = "doors",
            DOORS_LOUD = "doors_loud",
            FIRE = "fire",
            FIRE_LOUDER = "fire_louder",
            FRONTEND_GAME_LOUD = "frontend_game_loud",
            FRONTEND_MENU = "frontend_menu",
            FRONTEND_MENU_LOUD = "frontend_menu_loud",
            FRONTEND_RADIO = "frontend_radio",
            GAME_WORLD = "game_world",
            HUD = "hud",
            INTERACTIVE_MUSIC = "interactive_music",
            MELEE = "melee",
            MUSIC = "music",
            MUSIC_LOADING = "music_loading",
            PEDS = "peds",
            PEDS_CLOTHING = "peds_clothing",
            PEDS_COLLISIONS = "peds_collisions",
            PEDS_COLLISIONS_LOUD = "peds_collisions_loud",
            PEDS_WIND = "peds_wind",
            RADIO = "radio",
            SCORE = "score",
            SCRIPTED = "scripted",
            SCRIPTED_ALARMS = "scripted_alarms",
            SCRIPTED_LOUDER = "scripted_louder",
            SCRIPTED_TV = "scripted_tv",
            SPEECH = "speech",
            SPEECH_AMBIENT = "speech_ambient",
            SPEECH_BREATHING = "speech_breathing",
            SPEECH_PAIN = "speech_pain",
            SPEECH_SCRIPTED = "speech_scripted",
            UNDERWATER = "underwater",
            UNDERWATER_LOUD = "underwater_loud",
            UNDERWATER_MUTED = "underwater_muted",
            UNDERWATER_SWIMMING = "underwater_swimming",
            VEHICLES = "vehicles",
            VEHICLES_BICYCLES = "vehicles_bicycles",
            VEHICLES_BICYCLES_MECHANICAL = "vehicles_bicycles_mechanical",
            VEHICLES_BOATS_ENGINES = "vehicles_boats_engines",
            VEHICLES_BOATS_WATER = "vehicles_boats_water",
            VEHICLES_BRAKES = "vehicles_brakes",
            VEHICLES_CAR_BY = "vehicles_car_by",
            VEHICLES_CHASSIS_RATTLE = "vehicles_chassis_rattle",
            VEHICLES_DOORS = "vehicles_doors",
            VEHICLES_ENGINES_COOLING = "vehicles_engines_cooling",
            VEHICLES_ENGINES_DAMAGE = "vehicles_engines_damage",
            VEHICLES_ENGINES_IGNITION = "vehicles_engines_ignition",
            VEHICLES_ENGINES_INTAKE = "vehicles_engines_intake",
            VEHICLES_ENGINES_LOUD = "vehicles_engines_loud",
            VEHICLES_ENGINES_REFLECTIONS = "vehicles_engines_reflections",
            VEHICLES_ENGINES_STARTUP = "vehicles_engines_startup",
            VEHICLES_EXTRAS_LOUD = "vehicles_extras_loud",
            VEHICLES_HELIS = "vehicles_helis",
            VEHICLES_HELIS_DISTANT = "vehicles_helis_distant",
            VEHICLES_HORNS = "vehicles_horns",
            VEHICLES_HORNS_LOUD = "vehicles_horns_loud",
            VEHICLES_PLANES = "vehicles_planes",
            VEHICLES_PLANES_CLOSE = "vehicles_planes_close",
            VEHICLES_PLANES_DISTANT = "vehicles_planes_distant",
            VEHICLES_PLANES_EXTRAS = "vehicles_planes_extras",
            VEHICLES_PLANES_JET = "vehicles_planes_jet",
            VEHICLES_PLANES_PROP = "vehicles_planes_prop",
            VEHICLES_SIRENS = "vehicles_sirens",
            VEHICLES_SUSPENSION = "vehicles_suspension",
            VEHICLES_TRAIN = "vehicles_train",
            VEHICLES_TRAIN_BRAKES = "vehicles_train_brakes",
            VEHICLES_TRAIN_CARRIAGE = "vehicles_train_carriage",
            VEHICLES_TRAIN_CLACK = "vehicles_train_clack",
            VEHICLES_WHEELS = "vehicles_wheels",
            VEHICLES_WHEELS_LOUD = "vehicles_wheels_loud",
            VEHICLES_WHEELS_SKIDS = "vehicles_wheels_skids",
            WATER = "water",
            WATER_LOUD = "water_loud",
            WATER_OCEAN = "water_ocean",
            WATER_RIVER = "water_river",
            WATER_SWIMMING = "water_swimming",
            WEAPONS = "weapons",
            WEAPONS_EXPLOSIONS = "weapons_explosions",
            WEAPONS_EXPLOSIONS_LOUD = "weapons_explosions_loud",
            WEAPONS_GUNS = "weapons_guns",
            WEATHER = "weather",
            WEATHER_RAIN = "weather_rain",
            WEATHER_RAIN_HEAVY = "weather_rain_heavy",
            WEATHER_RAIN_PROPS = "weather_rain_props",
            WEATHER_THUNDER = "weather_thunder",
            WEATHER_WIND = "weather_wind",
            WEATHER_WIND_FOLIAGE = "weather_wind_foliage",
            x011F1827 = "0x011F1827",
            x01E27C7E = "0x01E27C7E",
            x02C7B342 = "0x02C7B342",
            x03D39751 = "0x03D39751",
            x044986F4 = "0x044986F4",
            x05403EE1 = "0x05403EE1",
            x05D22F30 = "0x05D22F30",
            x0607FDB8 = "0x0607FDB8",
            x0BE5A8C0 = "0x0BE5A8C0",
            x0D3C9D38 = "0x0D3C9D38",
            x0E212957 = "0x0E212957",
            x0E4CF672 = "0x0E4CF672",
            x11034592 = "0x11034592",
            x11D52176 = "0x11D52176",
            x1C507071 = "0x1C507071",
            x1E51E02F = "0x1E51E02F",
            x1F418253 = "0x1F418253",
            x1FF21B89 = "0x1FF21B89",
            x20230050 = "0x20230050",
            x25E385A7 = "0x25E385A7",
            x266E012E = "0x266E012E",
            x291E7FD7 = "0x291E7FD7",
            x2BA33BE9 = "0x2BA33BE9",
            x2EED1D0A = "0x2EED1D0A",
            x2F34D6FC = "0x2F34D6FC",
            x31A9A815 = "0x31A9A815",
            x32157574 = "0x32157574",
            x368CC071 = "0x368CC071",
            x3874EB6C = "0x3874EB6C",
            x39736A51 = "0x39736A51",
            x3A52AFA3 = "0x3A52AFA3",
            x3AA35DEF = "0x3AA35DEF",
            x3C496EED = "0x3C496EED",
            x3EB27392 = "0x3EB27392",
            x3F6594E4 = "0x3F6594E4",
            x414231B5 = "0x414231B5",
            x41ACDDFF = "0x41ACDDFF",
            x44E21C90 = "0x44E21C90",
            x45EB536F = "0x45EB536F",
            x4E8BCAED = "0x4E8BCAED",
            x4FFD9CA5 = "0x4FFD9CA5",
            x52BA33D4 = "0x52BA33D4",
            x53B27328 = "0x53B27328",
            x585863F0 = "0x585863F0",
            x5A6165D9 = "0x5A6165D9",
            x6244F855 = "0x6244F855",
            x63614939 = "0x63614939",
            x639A44A4 = "0x639A44A4",
            x6805AAC2 = "0x6805AAC2",
            x6A3DD9A1 = "0x6A3DD9A1",
            x6C742462 = "0x6C742462",
            x6D867E97 = "0x6D867E97",
            x6F56A5DC = "0x6F56A5DC",
            x75FB2B65 = "0x75FB2B65",
            x781669E6 = "0x781669E6",
            x7A6F1418 = "0x7A6F1418",
            x80722AAA = "0x80722AAA",
            x85B8BFD4 = "0x85B8BFD4",
            x85DBC375 = "0x85DBC375",
            x864AAAB9 = "0x864AAAB9",
            x88EEAE72 = "0x88EEAE72",
            x8A91FE75 = "0x8A91FE75",
            x9205C7A1 = "0x9205C7A1",
            x933E72C3 = "0x933E72C3",
            x94821026 = "0x94821026",
            x9748F077 = "0x9748F077",
            x992F6CB7 = "0x992F6CB7",
            x9B60B77E = "0x9B60B77E",
            x9C6A4771 = "0x9C6A4771",
            xA4D158B0 = "0xA4D158B0",
            xA6A84701 = "0xA6A84701",
            xA6DA13DC = "0xA6DA13DC",
            xA95BF404 = "0xA95BF404",
            xAA0678B2 = "0xAA0678B2",
            xAC3F546D = "0xAC3F546D",
            xACA58232 = "0xACA58232",
            xB2681B31 = "0xB2681B31",
            xB421C2DC = "0xB421C2DC",
            xB4C14B9C = "0xB4C14B9C",
            xB607457F = "0xB607457F",
            xB9CB44C7 = "0xB9CB44C7",
            xBAD598C7 = "0xBAD598C7",
            xBC11E471 = "0xBC11E471",
            xBC72B5EB = "0xBC72B5EB",
            xBCE6F3E0 = "0xBCE6F3E0",
            xBF162C33 = "0xBF162C33",
            xC4872161 = "0xC4872161",
            xC701057A = "0xC701057A",
            xC7D71D61 = "0xC7D71D61",
            xC8B2D787 = "0xC8B2D787",
            xCB2382B4 = "0xCB2382B4",
            xCD3365DE = "0xCD3365DE",
            xCFF0C1C2 = "0xCFF0C1C2",
            xD2626419 = "0xD2626419",
            xD3594A47 = "0xD3594A47",
            xD4AE89CA = "0xD4AE89CA",
            xD59675EA = "0xD59675EA",
            xDA38F55D = "0xDA38F55D",
            xDCA3CC61 = "0xDCA3CC61",
            xDF9CFFD4 = "0xDF9CFFD4",
            xE3FAF7D3 = "0xE3FAF7D3",
            xE86DF43F = "0xE86DF43F",
            xE8C16DEA = "0xE8C16DEA",
            xEA1277B9 = "0xEA1277B9",
            xEA185B02 = "0xEA185B02",
            xEB0390D7 = "0xEB0390D7",
            xEB0865AB = "0xEB0865AB",
            xED39E59D = "0xED39E59D",
            xF05AAEDD = "0xF05AAEDD",
            xF0E66096 = "0xF0E66096",
            xF1754C85 = "0xF1754C85",
            xF2C3426E = "0xF2C3426E",
            xF3196F77 = "0xF3196F77",
            xF48DE3B3 = "0xF48DE3B3",
            xF4908CAD = "0xF4908CAD",
            xF4FABC2A = "0xF4FABC2A",
            xF7954E76 = "0xF7954E76",
            xF7C35252 = "0xF7C35252",
            xF841C9F9 = "0xF841C9F9",
            xF846B110 = "0xF846B110",
            xFB40B82B = "0xFB40B82B",
            xFDB42EDF = "0xFDB42EDF",
            xFF7A0598 = "0xFF7A0598",
        }
        export const enum FileEncoding {
            UTF8 = "utf-8",
            UTF16 = "utf-16",
            BINARY = "binary",
        }
        export const enum ModelType {
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
            OBJECT,
        }
        export const enum KeyCode {
            KEY0 = 48,
            KEY1 = 49,
            KEY2 = 50,
            KEY3 = 51,
            KEY4 = 52,
            KEY5 = 53,
            KEY6 = 54,
            KEY7 = 55,
            KEY8 = 56,
            KEY9 = 57,
            BACKSPACE = 8,
            TAB = 9,
            CLEAR = 12,
            ENTER = 13,
            RETURN = 13,
            ESCAPE = 27,
            SPACE = 32,
            LEFT = 37,
            UP = 38,
            RIGHT = 39,
            DOWN = 40,
            DELETE = 46,
            INSERT = 45,
            HOME = 36,
            END = 35,
            PAGE_UP = 33,
            PAGE_DOWN = 34,
            CAPS_LOCK = 20,
            SHIFT = 16,
            ALT = 18,
            CTRL = 17,
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
            KP_MULTIPLY = 106,
            KP_ADD = 107,
            KP_SUBTRACT = 109,
            KP_DECIMAL = 110,
            KP_DIVIDE = 111,
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
            NUMPAD0 = 96,
            NUMPAD1 = 97,
            NUMPAD2 = 98,
            NUMPAD3 = 99,
            NUMPAD4 = 100,
            NUMPAD5 = 101,
            NUMPAD6 = 102,
            NUMPAD7 = 103,
            NUMPAD8 = 104,
            NUMPAD9 = 105,
            MOUSE_LEFT = 1,
            MOUSE_RIGHT = 2,
            MOUSE_MIDDLE = 4,
        }
        export const enum PedConfigFlag {
            NO_CRITICAL_HITS = 2,
            DROWNS_IN_WATER = 3,
            DISABLE_RETICULE_FIXED_LOCKON = 4,
            UPPER_BODY_DAMAGE_ANIMS_ONLY = 7,
            NEVER_LEAVES_GROUP = 13,
            BLOCK_NON_TEMPORARY_EVENTS = 17,
            CAN_PUNCH = 18,
            IGNORE_SEEN_MELEE = 24,
            GET_OUT_UNDRIVEABLE_VEHICLE = 29,
            CAN_FLY_THRU_WINDSCREEN = 32,
            DIES_WHEN_RAGDOLL = 33,
            HAS_HELMET = 34,
            PUT_ON_MOTORCYCLE_HELMET = 35,
            DONT_TAKE_OFF_HELMET = 36,
            DISABLE_EVASIVE_DIVES = 39,
            DONT_INFLUENCE_WANTED_LEVEL = 42,
            DISABLE_PLAYER_LOCKON = 43,
            DISABLE_LOCKON_TO_RANDOM_PEDS = 44,
            ALLOW_LOCKON_TO_FRIENDLY_PLAYERS = 45,
            BEING_DELETED = 47,
            BLOCK_WEAPON_SWITCHING = 48,
            NO_COLLISION = 52,
            IS_SHOOTING = 58,
            WAS_SHOOTING = 59,
            IS_ON_GROUND = 60,
            WAS_ON_GROUND = 61,
            IN_VEHICLE = 62,
            ON_MOUNT = 63,
            ATTACHED_TO_VEHICLE = 64,
            IS_SWIMMING = 65,
            WAS_SWIMMING = 66,
            IS_SKIING = 67,
            IS_SITTING = 68,
            KILLED_BY_STEALTH = 69,
            KILLED_BY_TAKEDOWN = 70,
            KNOCKEDOUT = 71,
            IS_SNIPER_SCOPE_ACTIVE = 72,
            SUPER_DEAD = 73,
            USING_COVER_POINT = 75,
            IS_IN_THE_AIR = 76,
            IS_AIMING_GUN = 78,
            FORCE_PED_LOAD_COVER = 93,
            VAULT_FROM_COVER = 97,
            IS_DRUNK = 100,
            FORCED_AIM = 101,
            IS_NOT_RAGDOLL_AND_NOT_PLAYING_ANIM = 104,
            FORCE_RELOAD = 105,
            DONT_ACTIVATE_RAGDOLL_FROM_VEHICLE_IMPACT = 106,
            DONT_ACTIVATE_RAGDOLL_FROM_BULLET_IMPACT = 107,
            DONT_ACTIVATE_RAGDOLL_FROM_EXPLOSIONS = 108,
            DONT_ACTIVATE_RAGDOLL_FROM_FIRE = 109,
            DONT_ACTIVATE_RAGDOLL_FROM_ELECTROCUTION = 110,
            KEEP_WEAPON_HOLSTERED_UNLESS_FIRED = 113,
            GET_OUT_BURNING_VEHICLE = 116,
            BUMPED_BY_PLAYER = 117,
            RUN_FROM_FIRES_AND_EXPLOSIONS = 118,
            TREAT_AS_PLAYER_DURING_TARGETING = 119,
            IS_HAND_CUFFED = 120,
            IS_ANKLE_CUFFED = 121,
            DISABLE_MELEE = 122,
            DISABLE_UNARMED_DRIVEBYS = 123,
            JUST_GETS_PULLED_OUT_WHEN_ELECTROCUTED = 124,
            NM_MESSAGE466 = 125,
            WILL_NOT_HOTWIRE_LAW_ENFORCEMENT_VEHICLE = 126,
            WILL_COMMANDEER_RATHER_THAN_JACK = 127,
            CAN_BE_AGITATED = 128,
            FORCE_PED_TO_FACE_LEFT_IN_COVER = 129,
            FORCE_PED_TO_FACE_RIGHT_IN_COVER = 130,
            BLOCK_PED_FROM_TURNING_IN_COVER = 131,
            KEEP_RELATIONSHIP_GROUP_AFTER_CLEAN_UP = 132,
            FORCE_PED_TO_BE_DRAGGED = 133,
            PREVENT_PED_FROM_REACTING_TO_BEING_JACKED = 134,
            IS_SCUBA = 135,
            WILL_ARREST_RATHER_THAN_JACK = 136,
            REMOVE_DEAD_EXTRA_FAR_AWAY = 137,
            RIDING_TRAIN = 138,
            ARREST_RESULT = 139,
            CAN_ATTACK_FRIENDLY = 140,
            WILL_JACK_ANY_PLAYER = 141,
            WILL_JACK_WANTED_PLAYERS_RATHER_THAN_STEAL_CAR = 144,
            SHOOTING_ANIM_FLAG = 145,
            DISABLE_LADDER_CLIMBING = 146,
            STAIRS_DETECTED = 147,
            SLOPE_DETECTED = 148,
            COWER_INSTEAD_OF_FLEE = 150,
            CAN_ACTIVATE_RAGDOLL_WHEN_VEHICLE_UPSIDE_DOWN = 151,
            ALWAYS_RESPOND_TO_CRIES_FOR_HELP = 152,
            DISABLE_BLOOD_POOL_CREATION = 153,
            SHOULD_FIX_IF_NO_COLLISION = 154,
            CAN_PERFORM_ARREST = 155,
            CAN_PERFORM_UNCUFF = 156,
            CAN_BE_ARRESTED = 157,
            PLAYER_PREFER_FRONT_SEAT_M_P = 159,
            IS_INJURED = 166,
            DONT_ENTER_VEHICLES_IN_PLAYERS_GROUP = 167,
            PREVENT_ALL_MELEE_TAUNTS = 169,
            IS_INJURED2 = 170,
            ALWAYS_SEE_APPROACHING_VEHICLES = 171,
            CAN_DIVE_AWAY_FROM_APPROACHING_VEHICLES = 172,
            ALLOW_PLAYER_TO_INTERRUPT_VEHICLE_ENTRY_EXIT = 173,
            ONLY_ATTACK_LAW_IF_PLAYER_IS_WANTED = 174,
            PEDS_JACKING_ME_DONT_GET_IN = 177,
            PED_IGNORES_ANIM_INTERRUPT_EVENTS = 179,
            IS_IN_CUSTODY = 180,
            FORCE_STANDARD_BUMP_REACTION_THRESHOLDS = 181,
            LAW_WILL_ONLY_ATTACK_IF_PLAYER_IS_WANTED = 182,
            IS_AGITATED = 183,
            PREVENT_AUTO_SHUFFLE_TO_DRIVERS_SEAT = 184,
            USE_KINEMATIC_MODE_WHEN_STATIONARY = 185,
            ENABLE_WEAPON_BLOCKING = 186,
            HAS_HURT_STARTED = 187,
            DISABLE_HURT = 188,
            PLAYER_IS_WEIRD = 189,
            DO_NOTHING_WHEN_ON_FOOT_BY_DEFAULT = 193,
            USING_SCENARIO = 194,
            VISIBLE_ON_SCREEN = 195,
            DONT_ACTIVATE_RAGDOLL_ON_VEHICLE_COLLISION_WHEN_DEAD = 199,
            HAS_BEEN_IN_ARMED_COMBAT = 200,
            AVOIDANCE_IGNORE_ALL = 202,
            AVOIDANCE_IGNORED_BY_ALL = 203,
            AVOIDANCE_IGNORE_GROUP1 = 204,
            AVOIDANCE_MEMBER_OF_GROUP1 = 205,
            FORCED_TO_USE_SPECIFIC_GROUP_SEAT_INDEX = 206,
            DISABLE_EXPLOSION_REACTIONS = 208,
            DODGED_PLAYER = 209,
            WAITING_FOR_PLAYER_CONTROL_INTERRUPT = 210,
            FORCED_TO_STAY_IN_COVER = 211,
            GENERATES_SOUND_EVENTS = 212,
            LISTENS_TO_SOUND_EVENTS = 213,
            ALLOW_TO_BE_TARGETED_IN_A_VEHICLE = 214,
            WAIT_FOR_DIRECT_ENTRY_POINT_TO_BE_FREE_WHEN_EXITING = 215,
            ONLY_REQUIRE_ONE_PRESS_TO_EXIT_VEHICLE = 216,
            FORCE_EXIT_TO_SKY_DIVE = 217,
            DONT_ENTER_LEADERS_VEHICLE = 220,
            DISABLE_EXIT_TO_SKY_DIVE = 221,
            SHRINK = 223,
            MELEE_COMBAT = 224,
            DISABLE_POTENTIAL_TO_BE_WALKED_INTO_RESPONSE = 225,
            DISABLE_PED_AVOIDANCE = 226,
            FORCE_RAGDOLL_UPON_DEATH = 227,
            DISABLE_PANIC_IN_VEHICLE = 229,
            ALLOWED_TO_DETACH_TRAILER = 230,
            IS_HOLDING_PROP = 236,
            BLOCKS_PATHING_WHEN_DEAD = 237,
            FORCE_SKIN_CHARACTER_CLOTH = 240,
            DISABLE_STOPPING_VEHICLE_ENGINE = 241,
            PHONE_DISABLE_TEXTING_ANIMATIONS = 242,
            PHONE_DISABLE_TALKING_ANIMATIONS = 243,
            PHONE_DISABLE_CAMERA_ANIMATIONS = 244,
            DISABLE_BLIND_FIRING_IN_SHOT_REACTIONS = 245,
            ALLOW_NEARBY_COVER_USAGE = 246,
            CAN_PLAY_IN_CAR_IDLES = 248,
            CAN_ATTACK_NON_WANTED_PLAYER_AS_LAW = 249,
            WILL_TAKE_DAMAGE_WHEN_VEHICLE_CRASHES = 250,
            A_I_CAN_DRIVE_PLAYER_AS_REAR_PASSENGER = 251,
            PLAYER_CAN_JACK_FRIENDLY_PLAYERS = 252,
            IS_ON_STAIRS = 253,
            A_I_DRIVER_ALLOW_FRIENDLY_PASSENGER_SEAT_ENTRY = 255,
            ALLOW_MISSION_PED_TO_USE_INJURED_MOVEMENT = 257,
            PREVENT_USING_LOWER_PRIORITY_SEATS = 261,
            DISABLE_CLOSING_VEHICLE_DOOR = 264,
            TELEPORT_TO_LEADER_VEHICLE = 268,
            AVOIDANCE_IGNORE_WEIRD_PED_BUFFER = 269,
            ON_STAIR_SLOPE = 270,
            DONT_BLIP_COP = 272,
            CLIMBED_SHIFTED_FENCE = 273,
            KILL_WHEN_TRAPPED = 275,
            EDGE_DETECTED = 276,
            AVOID_TEAR_GAS = 279,
            NO_WRITHE = 281,
            ONLY_USE_FORCED_SEAT_WHEN_ENTERING_HELI_IN_GROUP = 282,
            DISABLE_WEIRD_PED_EVENTS = 285,
            SHOULD_CHARGE_NOW = 286,
            RAGDOLLING_ON_BOAT = 287,
            HAS_BRANDISHED_WEAPON = 288,
            FREEZE_POSITION = 292,
            DISABLE_SHOCKING_EVENTS = 294,
            NEVER_REACT_TO_PED_ON_ROOF = 296,
            DISABLE_SHOCKING_DRIVING_ON_PAVEMENT_EVENTS = 299,
            DISABLE_PED_CONSTRAINTS = 301,
            FORCE_INITIAL_PEEK_IN_COVER = 302,
            DISABLE_JUMPING_FROM_VEHICLES_AFTER_LEADER = 305,
            IS_IN_CLUSTER = 310,
            SHOUT_TO_GROUP_ON_PLAYER_MELEE = 311,
            IGNORED_BY_AUTO_OPEN_DOORS = 312,
            NO_PED_MELEE = 314,
            CHECK_LO_S_FOR_SOUND_EVENTS = 315,
            CAN_SAY_FOLLOWED_BY_PLAYER_AUDIO = 317,
            ACTIVATE_RAGDOLL_FROM_MINOR_PLAYER_CONTACT = 318,
            FORCE_POSE_CHARACTER_CLOTH = 320,
            HAS_CLOTH_COLLISION_BOUNDS = 321,
            HAS_HIGH_HEELS = 322,
            DONT_BEHAVE_LIKE_LAW = 324,
            DISABLE_POLICE_INVESTIGATING_BODY = 326,
            DISABLE_WRITHE_SHOOT_FROM_GROUND = 327,
            LOWER_PRIORITY_OF_WARP_SEATS = 328,
            DISABLE_TALK_TO = 329,
            DONT_BLIP = 330,
            IS_SWITCHING_WEAPON = 331,
            IGNORE_LEG_IK_RESTRICTIONS = 332,
            ALLOW_TASK_DO_NOTHING_TIMESLICING = 339,
            NOT_ALLOWED_TO_JACK_ANY_PLAYERS = 342,
            ALWAYS_LEAVE_TRAIN_UPON_ARRIVAL = 345,
            ONLY_WRITHE_FROM_WEAPON_DAMAGE = 347,
            USE_SLO_MO_BLOOD_VFX = 348,
            EQUIP_JETPACK = 349,
            PREVENT_DRAGGED_OUT_OF_CAR_THREAT_RESPONSE = 350,
            FORCE_DEEP_SURFACE_CHECK = 356,
            DISABLE_DEEP_SURFACE_ANIMS = 357,
            DONT_BLIP_NOT_SYNCED = 358,
            IS_DUCKING_IN_VEHICLE = 359,
            PREVENT_AUTO_SHUFFLE_TO_TURRET_SEAT = 360,
            DISABLE_EVENT_INTERIOR_STATUS_CHECK = 361,
            HAS_RESERVE_PARACHUTE = 362,
            USE_RESERVE_PARACHUTE = 363,
            TREAT_DISLIKE_AS_HATE_WHEN_IN_COMBAT = 364,
            ONLY_UPDATE_TARGET_WANTED_IF_SEEN = 365,
            ALLOW_AUTO_SHUFFLE_TO_DRIVERS_SEAT = 366,
            PREVENT_REACTING_TO_SILENCED_CLONE_BULLETS = 372,
            DISABLE_INJURED_CRY_FOR_HELP_EVENTS = 373,
            NEVER_LEAVE_TRAIN = 374,
            DONT_DROP_JETPACK_ON_DEATH = 375,
            DISABLE_AUTO_EQUIP_HELMETS_IN_BIKES = 380,
            IS_CLIMBING_LADDER = 388,
            HAS_BARE_FEET = 389,
            GO_ON_WITHOUT_VEHICLE_IF_IT_IS_UNABLE_TO_GET_BACK_TO_ROAD = 391,
            BLOCK_DROPPING_HEALTH_SNACKS_ON_DEATH = 392,
            FORCE_THREAT_RESPONSE_TO_NON_FRIEND_TO_FRIEND_MELEE_ACTIONS = 394,
            DONT_RESPOND_TO_RANDOM_PEDS_DAMAGE = 395,
            ALLOW_CONTINUOUS_THREAT_RESPONSE_WANTED_LEVEL_UPDATES = 396,
            KEEP_TARGET_LOSS_RESPONSE_ON_CLEANUP = 397,
            PLAYERS_DONT_DRAG_ME_OUT_OF_CAR = 398,
            BROADCAST_REPONDED_TO_THREAT_WHEN_GOING_TO_POINT_SHOOTING = 399,
            IGNORE_PED_TYPE_FOR_IS_FRIENDLY_WITH = 400,
            TREAT_NON_FRIENDLY_AS_HATE_WHEN_IN_COMBAT = 401,
            DONT_LEAVE_VEHICLE_IF_LEADER_NOT_IN_VEHICLE = 402,
            ALLOW_MELEE_REACTION_IF_MELEE_PROOF_IS_ON = 404,
            USE_NORMAL_EXPLOSION_DAMAGE_WHEN_BLOWN_UP_IN_VEHICLE = 407,
            DISABLE_HOMING_MISSILE_LOCK_FOR_VEHICLE_PED_INSIDE = 408,
            DISABLE_TAKE_OFF_SCUBA_GEAR = 409,
            ALPHA = 410,
            LAW_PEDS_CAN_FLEE_FROM_NON_WANTED_PLAYER = 411,
            FORCE_BLIP_SECURITY_PEDS_IF_PLAYER_IS_WANTED = 412,
            IS_HOLSTERING_WEAPON = 413,
            USE_GO_TO_POINT_FOR_SCENARIO_NAVIGATION = 414,
            DONT_CLEAR_LOCAL_PASSENGERS_WANTED_LEVEL = 415,
            BLOCK_AUTO_SWAP_ON_WEAPON_PICKUPS = 416,
            THIS_PED_IS_A_TARGET_PRIORITY_FOR_A_I = 417,
            IS_SWITCHING_HELMET_VISOR = 418,
            FORCE_HELMET_VISOR_SWITCH = 419,
            FLAMING_FOOTPRINTS = 421,
            DISABLE_VEHICLE_COMBAT = 422,
            DISABLE_PROP_KNOCK_OFF = 423,
            FALLS_LIKE_AIRCRAFT = 424,
            USE_LOCKPICK_VEHICLE_ENTRY_ANIMATIONS = 426,
            IGNORE_INTERIOR_CHECK_FOR_SPRINTING = 427,
            SWAT_HELI_SPAWN_WITHIN_LAST_SPOTTED_LOCATION = 428,
            DISABLE_STARTING_VEHICLE_ENGINE = 429,
            IGNORE_BEING_ON_FIRE = 430,
            DISABLE_TURRET_OR_REAR_SEAT_PREFERENCE = 431,
            DISABLE_WANTED_HELICOPTER_SPAWNING = 432,
            USE_TARGET_PERCEPTION_FOR_CREATING_AIMED_AT_EVENTS = 433,
            DISABLE_HOMING_MISSILE_LOCKON = 434,
            FORCE_IGNORE_MAX_MELEE_ACTIVE_SUPPORT_COMBATANTS = 435,
            STAY_IN_DEFENSIVE_AREA_WHEN_IN_VEHICLE = 436,
            DONT_SHOUT_TARGET_POSITION = 437,
            DISABLE_HELMET_ARMOR = 438,
            PREVENT_VEH_EXIT_DUE_TO_INVALID_WEAPON = 441,
            IGNORE_NET_SESSION_FRIENDLY_FIRE_CHECK_FOR_ALLOW_DAMAGE = 442,
            DONT_LEAVE_COMBAT_IF_TARGET_PLAYER_IS_ATTACKED_BY_POLICE = 443,
            CHECK_LOCKED_BEFORE_WARP = 444,
            DONT_SHUFFLE_IN_VEHICLE_TO_MAKE_ROOM = 445,
            GIVE_WEAPON_ON_GETUP = 446,
            DONT_HIT_VEHICLE_WITH_PROJECTILES = 447,
            DISABLE_FORCED_ENTRY_FOR_OPEN_VEHICLES_FROM_TRY_LOCKED_DOOR = 448,
            FIRES_DUMMY_ROCKETS = 449,
            IS_ARRESTING = 450,
            IS_DECOY_PED = 451,
            HAS_ESTABLISHED_DECOY = 452,
            BLOCK_DISPATCHED_HELICOPTERS_FROM_LANDING = 453,
            DONT_CRY_FOR_HELP_ON_STUN = 454,
            CAN_BE_INCAPACITATED = 456,
            MUTABLE_FORCED_AIM = 457,
            DONT_CHANGE_TARGET_FROM_MELEE = 458,
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
