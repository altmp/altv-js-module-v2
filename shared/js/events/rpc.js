const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.SCRIPT_RPC_EVENT, "ScriptRPC");
Event.register(alt.Enums.EventType.SCRIPT_RPC_ANSWER_EVENT, "ScriptRPCAnswer");
