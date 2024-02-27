/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class RmlDocument extends alt.RmlDocument {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [url] = args;

        return alt.RmlDocument.create({ url });
    }

    get isVisible() {
        return this.visible;
    }

    get isModal() {
        return this.modal;
    }
}

alt.RmlDocument.setFactory(RmlDocument);

cppBindings.registerCompatibilityExport("RmlDocument", RmlDocument);
