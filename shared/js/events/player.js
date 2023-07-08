const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_CHANGE_ANIMATION_EVENT, "PlayerAnimationChange");
Event.register(alt.Enums.EventType.PLAYER_WEAPON_CHANGE, "PlayerWeaponChange");
