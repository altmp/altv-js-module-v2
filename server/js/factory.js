const { setEntityFactory, getEntityFactory } = requireBinding("shared/factory.js");

alt.Factory.setColShapeFactory = setEntityFactory(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);

alt.Factory.getColShapeFactory = getEntityFactory(alt.Enums.BaseObjectType.COLSHAPE);

// Factory ctors
alt.Vehicle.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.VEHICLE, ctx);
};

alt.ColShape.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapeSphere.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.SPHERE;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapeCylinder.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CYLINDER;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapeCircle.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CIRCLE;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapeCuboid.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CUBOID;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapeRectangle.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.RECT;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.ColshapePolygon.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.POLYGON;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

alt.Checkpoint.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");
    ctx.colShapeType = alt.Enums.ColShapeType.CHECKPOINT_CYLINDER;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.COLSHAPE, ctx);
};

