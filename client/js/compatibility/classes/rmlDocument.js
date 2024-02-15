/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class RmlDocument extends alt.RmlDocument {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [url] = args;

        return alt.RmlDocument.create({ url });
    }
}

extendAltEntityClass(RmlDocument, BaseObject);

alt.RmlDocument.setFactory(RmlDocument);

cppBindings.registerCompatibilityExport("RmlDocument", RmlDocument);
