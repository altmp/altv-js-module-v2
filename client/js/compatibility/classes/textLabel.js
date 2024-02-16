/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("client/factory.js");

class TextLabel extends alt.TextLabel {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [text, fontName, fontSize, fontScale, pos, rot, color, outlineWidth, outlineColor, useStreaming, streamingDistance] = args;

        return alt.TextLabel.create({ text, fontName, fontSize, fontScale, pos, rot, color, outlineWidth, outlineColor, useStreaming, streamingDistance });
    }
}

alt.TextLabel.setFactory(TextLabel);

cppBindings.registerCompatibilityExport("TextLabel", TextLabel);
