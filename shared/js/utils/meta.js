/** @type {typeof import("./../utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

function addLocalMetaListener(key, handler) {
    assertIsType(key, "string", "key must be a string");
    assertIsType(handler, "function", "handler must be a function");

    const wrapper = (ctx) => {
        if (ctx.key !== key) return;
        handler(ctx);
    };

    return alt.Events.onLocalMetaChange(wrapper);
}

function addStreamSyncedMetaListener(key, handler) {
    assertIsType(key, "string", "key must be a string");
    assertIsType(handler, "function", "handler must be a function");

    const wrapper = (ctx) => {
        if (ctx.key !== key) return;
        handler(ctx);
    };

    return alt.Events.onStreamSyncedMetaChange(wrapper);
}

alt.Utils.addLocalMetaListener = addLocalMetaListener;
alt.Utils.addStreamSyncedMetaListener = addStreamSyncedMetaListener;
