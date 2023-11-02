const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_CHANGE_ANIMATION_EVENT, "PlayerAnimationChange");
Event.register(alt.Enums.EventType.PLAYER_WEAPON_CHANGE, "PlayerWeaponChange");
Event.register(alt.Enums.EventType.PLAYER_ENTERING_VEHICLE, "PlayerStartVehicleEnter");
Event.register(alt.Enums.EventType.PLAYER_ENTER_VEHICLE, "PlayerVehicleEntered");
Event.register(alt.Enums.EventType.PLAYER_LEAVE_VEHICLE, "PlayerVehicleLeft");
Event.register(alt.Enums.EventType.PLAYER_CHANGE_VEHICLE_SEAT, "PlayerVehicleSeatChange");

Event.register(alt.Enums.EventType.PLAYER_START_TALKING, "PlayerStartTalking");
Event.register(alt.Enums.EventType.PLAYER_STOP_TALKING, "PlayerStopTalking");
