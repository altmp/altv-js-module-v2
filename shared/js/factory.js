/** @type {typeof import("./utils.js")} */
const { assert, assertIsObject } = requireBinding("shared/utils.js");

export function setEntityFactory(altClass, type) {
    return (factory) => {
        assert(
            typeof factory === "function" && altClass.isPrototypeOf(factory),
            `Factory has to inherit from alt.${altClass.name}`
        );
        assert(factory.length === 0, `Factory constructor has to have no arguments`);

        cppBindings.setEntityFactory(type, factory);
    };
}

export function getEntityFactory(type) {
    return () => {
        return cppBindings.getEntityFactory(type);
    };
}

alt.Factory.setPlayerFactory = setEntityFactory(alt.Player, alt.Enums.BaseObjectType.PLAYER);
alt.Factory.getPlayerFactory = getEntityFactory(alt.Enums.BaseObjectType.PLAYER);

alt.Factory.setVehicleFactory = setEntityFactory(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
alt.Factory.getVehicleFactory = getEntityFactory(alt.Enums.BaseObjectType.VEHICLE);

alt.Factory.setPedFactory = setEntityFactory(alt.Ped, alt.Enums.BaseObjectType.PED);
alt.Factory.getPedFactory = getEntityFactory(alt.Enums.BaseObjectType.PED);

alt.Factory.setBlipFactory = setEntityFactory(alt.Blip, alt.Enums.BaseObjectType.BLIP);
alt.Factory.getBlipFactory = getEntityFactory(alt.Enums.BaseObjectType.BLIP);

alt.Factory.setVirtualEntityFactory = setEntityFactory(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
alt.Factory.getVirtualEntityFactory = getEntityFactory(alt.Enums.BaseObjectType.VIRTUAL_ENTITY);

alt.Factory.setVirtualEntityGroupFactory = setEntityFactory(
    alt.VirtualEntityGroup,
    alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP
);
alt.Factory.getVirtualEntityGroupFactory = getEntityFactory(alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

alt.Factory.setColShapeFactory = setEntityFactory(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);
alt.Factory.getColShapeFactory = getEntityFactory(alt.Enums.BaseObjectType.COLSHAPE);

alt.Factory.setNetworkObjectFactory = setEntityFactory(alt.NetworkObject, alt.Enums.BaseObjectType.NETWORK_OBJECT);
alt.Factory.getNetworkObjectFactory = getEntityFactory(alt.Enums.BaseObjectType.NETWORK_OBJECT);

// Factory ctors
alt.PointBlip.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.blipType = alt.Enums.BlipType.DESTINATION;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};

alt.AreaBlip.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.blipType = alt.Enums.BlipType.AREA;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};

alt.RadiusBlip.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    ctx.blipType = alt.Enums.BlipType.RADIUS;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};

alt.VirtualEntity.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.VIRTUAL_ENTITY, ctx);
};

alt.VirtualEntityGroup.create = (ctx) => {
    assertIsObject(ctx, "Invalid args");
    return cppBindings.createEntity(alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP, ctx);
};
