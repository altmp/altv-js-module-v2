const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_CHANGE_ANIMATION_EVENT, "PlayerAnimationChange");
Event.register(alt.Enums.EventType.PLAYER_WEAPON_CHANGE, "PlayerWeaponChange");
Event.register(alt.Enums.EventType.PLAYER_ENTER_VEHICLE, "PlayerEnteredVehicle");
Event.register(alt.Enums.EventType.PLAYER_ENTERING_VEHICLE, "PlayerEnteringVehicle");
Event.register(alt.Enums.EventType.PLAYER_LEAVE_VEHICLE, "PlayerLeftVehicle");
Event.register(alt.Enums.EventType.PLAYER_CHANGE_VEHICLE_SEAT, "PlayerVehicleSeatChange");
