interface Alt {
    /**
     * Emits specified event across particular client.
     *
     * @param eventName Name of the event.
     * @param args Rest parameters for emit to send.
     */
    emit<E extends keyof import("@altv/shared").Events.CustomWebViewToClientEvent>(eventName: E, ...args: Parameters<import("@altv/shared").Events.CustomWebViewToClientEvent[E]>): void;
    emit<E extends string>(eventName: Exclude<E, keyof import("@altv/shared").Events.CustomWebViewToClientEvent>, ...args: unknown[]): void;

    /**
     * Unsubscribes from client event handler with specified listener.
     *
     * @remarks Listener should be of the same reference as when event was subscribed.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be removed.
     */
    off<E extends keyof import("@altv/shared").Events.CustomWebViewToClientEvent>(eventName: E, listener: import("@altv/shared").Events.CustomWebViewToClientEvent[E]): void;
    off<E extends string>(eventName: Exclude<E, keyof import("@altv/shared").Events.CustomWebViewToClientEvent>, listener: (...args: unknown[]) => void): void;

    /**
     * Subscribes to client event handler with specified listener.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be added.
     */
    on<E extends keyof import("@altv/shared").Events.CustomClientToWebViewEvent>(eventName: E, listener: import("@altv/shared").Events.CustomClientToWebViewEvent[E]): void;
    on<E extends string>(eventName: Exclude<E, keyof import("@altv/shared").Events.CustomClientToWebViewEvent>, listener: (...args: unknown[]) => void): void;

    /**
     * Subscribes to client event with specified listener, which only triggers once.
     *
     * @param eventName Name of the event.
     * @param listener Listener that should be added.
     */
    once<E extends keyof import("@altv/shared").Events.CustomClientToWebViewEvent>(eventName: E, listener: import("@altv/shared").Events.CustomClientToWebViewEvent[E]): void;
    once<E extends string>(eventName: Exclude<E, keyof import("@altv/shared").Events.CustomClientToWebViewEvent>, listener: (...args: unknown[]) => void): void;

    readonly listeners: Readonly<Record<string, ((...args: unknown[]) => void)[]>>;

    getVersion(): string;
    getBranch(): string;
    getLocale(): string;
}

interface Window {
    alt: Alt;
}

declare var alt: Alt;
