/** @type {typeof import("../../../shared/js/helpers/enums.js")} */
const { createNumericEnum } = requireBinding("shared/helpers/enums.js");

// When changing, update types/shared/index.d.ts aswell
alt.Enums.VehicleLockState = createNumericEnum(["NONE", "UNLOCKED", "LOCKED", "LOCKOUT_PLAYER_ONLY", "LOCK_PLAYER_INSIDE", "INITIALLY_LOCKED", "FORCE_DOORS_SHUT", "LOCKED_CAN_BE_DAMAGED"]);
