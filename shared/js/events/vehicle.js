// clang-format off
const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.VEHICLE_DESTROY, "VehicleDestroy");
Event.register(alt.Enums.EventType.VEHICLE_ATTACH, "VehicleAttach");
Event.register(alt.Enums.EventType.VEHICLE_DETACH, "VehicleDetach");
Event.register(alt.Enums.EventType.VEHICLE_DAMAGE, "VehicleDamage");
