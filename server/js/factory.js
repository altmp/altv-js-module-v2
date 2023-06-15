/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("VoiceChannel", alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);

// Factory ctors
alt.Vehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VEHICLE);

alt.Ped.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.PED);

alt.NetworkObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.NETWORK_OBJECT);

alt.ColShape.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE);

alt.ColShapeSphere.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.SPHERE));

alt.ColShapeCylinder.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CYLINDER));

alt.ColShapeCircle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CIRCLE));

alt.ColShapeCuboid.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CUBOID));

alt.ColShapeRectangle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.RECTANGLE));

alt.ColShapePolygon.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.POLYGON));

alt.Checkpoint.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CHECKPOINT_CYLINDER));

alt.VoiceChannel.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VOICE_CHANNEL);
