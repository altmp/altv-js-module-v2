/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

const { WorldObject } = requireBinding("server/compatibility/classes/worldObject.js");
const { BaseObject } = requireBinding("server/compatibility/classes/baseObject.js");

const { extendAltEntityClass } = requireBinding("shared/compatibility/utils/classes.js");

class ColshapePolygon extends alt.ColShape {
    constructor(...args) {
        if (!args.length) return super();

        const [minZ, maxZ, points] = args;

        return alt.ColShapePolygon.create({
            minZ,
            maxZ,
            points
        });
    }
}

extendAltEntityClass(ColshapePolygon, WorldObject, BaseObject);

cppBindings.registerCompatibilityExport("ColshapePolygon", ColshapePolygon);
