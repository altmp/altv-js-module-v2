/** @type {typeof import("./utils.js")} */
const { assert, assertIsObject } = requireBinding("shared/utils.js");

registerFactory("Player", alt.Player, alt.Enums.BaseObjectType.PLAYER);
registerFactory("Vehicle", alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
registerFactory("Ped", alt.Ped, alt.Enums.BaseObjectType.PED);
registerFactory("Blip", alt.Blip, alt.Enums.BaseObjectType.BLIP);
registerFactory("VoiceChannel", alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);
registerFactory("ColShape", alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);
registerFactory("NetworkObject", alt.NetworkObject, alt.Enums.BaseObjectType.NETWORK_OBJECT);
registerFactory("Checkpoint", alt.Checkpoint, alt.Enums.BaseObjectType.CHECKPOINT);
registerFactory("VirtualEntity", alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
registerFactory("VirtualEntityGroup", alt.VirtualEntityGroup, alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

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

// Helpers
function setEntityFactory(altClass, type) {
    return (factory) => {
        assert(
            typeof factory === "function" && altClass.isPrototypeOf(factory),
            `Factory has to inherit from alt.${altClass.name}`
        );
        assert(factory.length === 0, `Factory constructor has to have no arguments`);

        cppBindings.setEntityFactory(type, factory);
    };
}

function getEntityFactory(type) {
    return () => {
        return cppBindings.getEntityFactory(type);
    };
}

export function registerFactory(name, altClass, type) {
    alt.Factory[`set${name}Factory`] = setEntityFactory(altClass, type);
    alt.Factory[`get${name}Factory`] = getEntityFactory(type);
}
