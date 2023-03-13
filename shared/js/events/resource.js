// clang-format off
const { Event } = requireBinding("shared/events.js");

Event.register("RESOURCE_START", "ResourceStart", true);
Event.register("RESOURCE_STOP", "ResourceStop", true);
