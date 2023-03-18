// clang-format off
const { Event } = requireBinding("shared/events.js");

Event.register("RESOURCE_START", "ResourceStart");
Event.register("RESOURCE_STOP", "ResourceStop");
Event.register("RESOURCE_ERROR", "ResourceError");
