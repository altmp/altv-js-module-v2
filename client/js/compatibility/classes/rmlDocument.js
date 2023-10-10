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

        const instance = alt.RmlDocument.create({ url });

        // TODO (xLuxy): Might need to also extend RmlElement manually
        return extendAltEntityClass(instance, BaseObject);
    }
}

alt.Factory.setRmlDocumentFactory(RmlDocument);
cppBindings.registerCompatibilityExport("RmlDocument", RmlDocument);
