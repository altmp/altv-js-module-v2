/** @type {typeof import("./utils.js")} */
const { assert } = requireBinding("shared/utils.js");

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
alt.Factory.setVehicleFactory = setEntityFactory(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);

alt.Factory.getPlayerFactory = getEntityFactory(alt.Enums.BaseObjectType.PLAYER);
alt.Factory.getVehicleFactory = getEntityFactory(alt.Enums.BaseObjectType.VEHICLE);

alt.Factory.setPedFactory = setEntityFactory(alt.Ped, alt.Enums.BaseObjectType.PED);
alt.Factory.getPedFactory = getEntityFactory(alt.Enums.BaseObjectType.PED);

alt.Factory.setBlipFactory = setEntityFactory(alt.Blip, alt.Enums.BaseObjectType.BLIP);
alt.Factory.getBlipFactory = getEntityFactory(alt.Enums.BaseObjectType.BLIP);

// Factory ctors
alt.PointBlip.create = (ctx) => {
    assert(typeof ctx === "object", "Invalid args");
    ctx.blipType = alt.Enums.BlipType.DESTINATION;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};

alt.AreaBlip.create = (ctx) => {
    assert(typeof ctx === "object", "Invalid args");
    ctx.blipType = alt.Enums.BlipType.AREA;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};

alt.RadiusBlip.create = (ctx) => {
    assert(typeof ctx === "object", "Invalid args");
    ctx.blipType = alt.Enums.BlipType.RADIUS;
    return cppBindings.createEntity(alt.Enums.BaseObjectType.BLIP, ctx);
};
