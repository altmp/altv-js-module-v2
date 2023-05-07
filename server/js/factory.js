/** @type {typeof import("../../shared/js/utils.js")} */
const { assert, assertIsObject } = requireBinding("shared/utils.js");
/** @type {typeof import("../../shared/js/factory.js")} */
const { setEntityFactory, getEntityFactory } = requireBinding("shared/factory.js");

alt.Factory.setVoiceChannelFactory = setEntityFactory(alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);
alt.Factory.getVoiceChannelFactory = getEntityFactory(alt.Enums.BaseObjectType.VOICE_CHANNEL);

// Factory ctors
alt.Vehicle.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.VEHICLE, ctx);
};

alt.Ped.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.PED, ctx);
};

alt.NetworkObject.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.NETWORK_OBJECT, ctx);
};

alt.ColShape.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapeSphere.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.SPHERE;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapeCylinder.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CYLINDER;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapeCircle.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CIRCLE;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapeCuboid.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CUBOID;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapeRectangle.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.RECT;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColShapePolygon.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.POLYGON;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.Checkpoint.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CHECKPOINT_CYLINDER;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.VoiceChannel.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.VOICE_CHANNEL, ctx);
};
