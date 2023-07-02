const { Event } = requireBinding("shared/events.js");

Event.register(alt.Enums.EventType.CONNECTION_COMPLETE, "ConnectionComplete");
Event.register(alt.Enums.EventType.DISCONNECT_EVENT, "Disconnect");
Event.register(alt.Enums.EventType.KEYBOARD_EVENT, "KeyBoardEvent");
Event.register(alt.Enums.EventType.WEB_VIEW_EVENT, "WebViewEvent");
Event.register(alt.Enums.EventType.WEB_SOCKET_CLIENT_EVENT, "WebSocketEvent");
Event.register(alt.Enums.EventType.AUDIO_EVENT, "AudioEvent");
Event.register(alt.Enums.EventType.SPAWNED, "Spawned");
Event.register(alt.Enums.EventType.RMLUI_EVENT, "RmluiEvent");
Event.register(alt.Enums.EventType.WINDOW_FOCUS_CHANGE, "WindowFocusChange");
Event.register(alt.Enums.EventType.WINDOW_RESOLUTION_CHANGE, "WindowResolutionChange");

// Custom keyboard events
Event.register(alt.Enums.CustomEventType.KEY_UP, "KeyUp", true);
Event.register(alt.Enums.CustomEventType.KEY_DOWN, "KeyDown", true);

alt.Events.onKeyBoardEvent(({ state, key }) => {
    if (state == "UP") Event.invoke(alt.Enums.CustomEventType.KEY_UP, { key: key }, true);
    else if (state == "DOWN") Event.invoke(alt.Enums.CustomEventType.KEY_DOWN, { key: key }, true);
});
