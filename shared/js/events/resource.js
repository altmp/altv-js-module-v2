// clang-format off
const alt = __alt;

const { Event } = getBinding("shared/events.js");

Event.register("RESOURCE_START", "ResourceStart", true);
Event.register("RESOURCE_STOP", "ResourceStop", true);
