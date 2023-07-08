const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.PLAYER_WEAPON_SHOOT_EVENT, "PlayerWeaponShoot");
Event.register(alt.Enums.EventType.PLAYER_BULLET_HIT_EVENT, "PlayerBulletHit");
Event.register(alt.Enums.EventType.PLAYER_WEAPON_CHANGE, "PlayerWeaponChange");
