function addLocalMetaListener(key, handler) {
    if (typeof key != "string") throw new Error("key must be a string");
    if (typeof handler != "function") throw new Error("handler must be a function");

    const wrapper = (ctx) => {
        if (ctx.key !== key) return;
        handler(ctx);
    };

    return alt.Events.onLocalMetaChange(wrapper);
}

function addSyncedMetaListener(key, handler) {
    if (typeof key != "string") throw new Error("key must be a string");
    if (typeof handler != "function") throw new Error("handler must be a function");

    const wrapper = (ctx) => {
        if (ctx.key !== key) return;
        handler(ctx);
    };

    return alt.Events.onSyncedMetaChange(wrapper);
}

function addStreamSyncedMetaListener(key, handler) {
    if (typeof key != "string") throw new Error("key must be a string");
    if (typeof handler != "function") throw new Error("handler must be a function");

    const wrapper = (ctx) => {
        if (ctx.key !== key) return;
        handler(ctx);
    };

    return alt.Events.onStreamSyncedMetaChange(wrapper);
}

alt.Utils.addLocalMetaListener = addLocalMetaListener;
alt.Utils.addSyncedMetaListener = addSyncedMetaListener;
alt.Utils.addStreamSyncedMetaListener = addStreamSyncedMetaListener;
