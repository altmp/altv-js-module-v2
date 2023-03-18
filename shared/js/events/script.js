// clang-format off
const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, "ServerScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, "ClientScriptEvent");
Event.register(alt.Enums.EventType.COLSHAPE_EVENT, "Colshape");
Event.register(alt.Enums.EventType.WEAPON_DAMAGE_EVENT, "WeaponDamage");
Event.register(alt.Enums.EventType.EXPLOSION_EVENT, "Explosion");
Event.register(alt.Enums.EventType.FIRE_EVENT, "Fire");
Event.register(alt.Enums.EventType.START_PROJECTILE_EVENT, "StartProjectile");
Event.register(alt.Enums.EventType.SYNCED_META_CHANGE, "SyncedMetaChange");
Event.register(alt.Enums.EventType.STREAM_SYNCED_META_CHANGE, "StreamSyncedMetaChange");
Event.register(alt.Enums.EventType.GLOBAL_META_CHANGE, "GlobalMetaChange");
Event.register(alt.Enums.EventType.GLOBAL_SYNCED_META_CHANGE, "GlobalSyncedMetaChange");
