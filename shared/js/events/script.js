const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SERVER_SCRIPT_EVENT, alt.isClient ? "RemoteScriptEvent" : "LocalScriptEvent");
Event.register(alt.Enums.EventType.CLIENT_SCRIPT_EVENT, alt.isClient ? "LocalScriptEvent" : "RemoteScriptEvent");
