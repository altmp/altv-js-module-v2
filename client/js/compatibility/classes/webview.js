/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { assert, assertIsType, isObject } = requireBinding("shared/utils.js");

class WebView extends alt.WebView {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const url = args[0];

        assert(args.length >= 1 && args.length <= 4, "Minimum 1, maximum 4 arguments expected");

        let instance = null;
        if (args.length == 4) {
            const [_, isOverlay, pos, size] = args;
            instance = alt.WebView.create({ url, isOverlay, pos, size });
        } else if (args.length == 3 && isObject(args[2])) {
            const [_, pos, size] = args;
            instance = alt.WebView.create({ url, pos, size });
        } else if (args.length == 3) {
            const [_, drawable, targetTexture] = args;
            instance = alt.WebView.create({ url, drawable, targetTexture });
        } else if (args.length == 2 && isObject(args[1])) {
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
        return `WebView{ url: ${this.url} }`;
    }

    get isVisible() {
        return this.visible;
    }

    set isVisible(state) {
        this.visible = state;
    }

    focus() {
        this.focused = true;
    }

    unfocus() {
        this.focused = false;
    }

    getOutputs() {
        return this.outputs;
    }

    getEventListeners(eventName) {
        assertIsType(eventName, "string", `Expeced eventName to be a string but got ${typeof eventName}`);

        return alt.WebView.listeners[eventName] ?? [];
    }

    toString() {
        return `WebView{ url: "${this.url}" }`;
    }
}

alt.WebView.setFactory(WebView);

cppBindings.registerCompatibilityExport("WebView", WebView);
