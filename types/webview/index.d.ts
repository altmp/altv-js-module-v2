import altShared from "@altv/shared";

interface Alt {
    /**
     * Emits specified event across particular client.
     *
     * @param eventName Name of the event.
     * @param args Rest parameters for emit to send.
     */
    emit<E extends keyof altShared.Events.CustomWebViewToClientEvent>(eventName: E, ...args: Parameters<altShared.Events.CustomWebViewToClientEvent[E]>): void;

    /**
     * Unsubscribes from client event handler with specified listener.
     *
     * @remarks Listener should be of the same reference as when event was subscribed.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be removed.
     */
    off<E extends keyof altShared.Events.CustomWebViewToClientEvent>(eventName: E, listener: altShared.Events.CustomWebViewToClientEvent[E]): void;

    /**
     * Subscribes to client event handler with specified listener.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be added.
     */
    on<E extends keyof altShared.Events.CustomClientToWebViewEvent>(eventName: E, listener: altShared.Events.CustomClientToWebViewEvent[E]): void;

    /**
     * Subscribes to client event with specified listener, which only triggers once.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be added.
     */
    once<E extends keyof altShared.Events.CustomClientToWebViewEvent>(eventName: E, listener: altShared.Events.CustomClientToWebViewEvent[E]): void;

    /**
     * Gets all the listeners for the specified webview event.
     *
     * @param eventName Name of the event.
     * @returns Array of listener functions for that event.
     */
    getEventListeners<E extends keyof altShared.Events.CustomClientToWebViewEvent>(eventName: E): (altShared.Events.CustomClientToWebViewEvent[E])[];

    getVersion(): string;
    getBranch(): string;
    getLocale(): string;
}

interface Window {
    alt: Alt;
  }

  declare var alt: Alt;
