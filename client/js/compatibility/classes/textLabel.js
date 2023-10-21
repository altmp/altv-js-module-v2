/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

const { WorldObject } = requireBinding("client/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("client/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class TextLabel extends alt.TextLabel {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [text, fontName, fontSize, fontScale, pos, rot, color, outlineWidth, outlineColor, useStreaming, streamingDistance] = args;

        const instance = alt.TextLabel.create({ text, fontName, fontSize, fontScale, pos, rot, color, outlineWidth, outlineColor, useStreaming, streamingDistance });
        return extendAltEntityClass(instance, WorldObject, BaseObject);
    }
}

alt.TextLabel.setFactory(TextLabel);
cppBindings.registerCompatibilityExport("TextLabel", TextLabel);
