/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("server/factory.js");

class _Object extends alt.Object {
    constructor(...args) {
        // NOTE (xLuxy): This prevents the infinite loop caused by alt.*.create
        if (!args.length) return super();

        const [model, pos, rot, alpha, textureVariation, lodDistance, streamingDistance] = args;

        return alt.Object.create({
            model,
            pos,
            rot,
            alpha,
            textureVariation,
            lodDistance,
            streamingDistance
        });
    }

    static get count() {
        return alt.Object.all.length;
    }
}

alt.Object.setFactory(_Object);

cppBindings.registerCompatibilityExport("Object", _Object);
