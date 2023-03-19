function setEntityFactory(altClass, type) {
    return (factory) => {
        if(typeof factory !== 'function' || !altClass.isPrototypeOf(factory)) throw new Error(`Factory has to inherit from alt.${altClass.name}`);
        if(factory.length !== 0) throw new Error(`Factory constructor has to have no arguments`);
        cppBindings.setEntityFactory(type, factory);
    };
}

function getEntityFactory(type) {
    return () => {
        return cppBindings.getEntityFactory(type);
    };
}

alt.Factory.setPlayerFactory = setEntityFactory(alt.Player, alt.Enums.BaseObjectType.PLAYER);
alt.Factory.setVehicleFactory = setEntityFactory(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
alt.Factory.setColShapeFactory = setEntityFactory(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);

alt.Factory.getPlayerFactory = getEntityFactory(alt.Enums.BaseObjectType.PLAYER);
alt.Factory.getVehicleFactory = getEntityFactory(alt.Enums.BaseObjectType.VEHICLE);
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
