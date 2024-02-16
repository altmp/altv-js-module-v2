/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assertIsType } = requireBinding("shared/utils.js");

class WebView extends alt.WebView {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const url = args[0];

        let instance = null;
        if (args.length == 4) {
            const [_, isOverlay, pos, size] = args;
            instance = alt.WebView.create({ url, isOverlay, pos, size });
        } else if (args.length == 3 && typeof args[2] == "object") {
            const [_, pos, size] = args;
            instance = alt.WebView.create({ url, pos, size });
        } else if (args.length == 3) {
            const [_, drawable, targetTexture] = args;
            instance = alt.WebView.create({ url, drawable, targetTexture });
        } else if (args.length == 2 && typeof args[1] == "object") {
            const [_, pos] = args;
            alt.WebView.create({ url, pos });
        } else if (args.length == 2) {
            const isOverlay = args[1];
            instance = alt.WebView.create({ url, isOverlay });
        } else {
            instance = alt.WebView.create({ url });
        }

        return instance;
    }

    static get count() {
        return alt.WebView.all.length;
    }

    toString() {
        return `WebView{ url: ${super.url} }`;
    }

    get isVisible() {
        return super.visible;
    }

    set isVisible(state) {
        super.visible = state;
    }

    focus() {
        super.focused = true;
    }

    unfocus() {
        super.focused = false;
    }

    getOutputs() {
        return super.outputs;
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expeced eventName to be a string but got ${typeof eventName}`);

        return alt.WebView.listeners[eventName] ?? [];
    }
}

alt.WebView.setFactory(WebView);

cppBindings.registerCompatibilityExport("WebView", WebView);
