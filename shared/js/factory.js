/** @type {typeof import("./utils.js")} */
const { assert, assertIsObject } = requireBinding("shared/utils.js");

registerFactory("Player", alt.Player, alt.Enums.BaseObjectType.PLAYER);
registerFactory("Vehicle", alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
registerFactory("Ped", alt.Ped, alt.Enums.BaseObjectType.PED);
registerFactory("Blip", alt.Blip, alt.Enums.BaseObjectType.BLIP);
registerFactory("ColShape", alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);
registerFactory("Object", alt.Object, alt.Enums.BaseObjectType.OBJECT);
registerFactory("Checkpoint", alt.Checkpoint, alt.Enums.BaseObjectType.CHECKPOINT);
registerFactory("VirtualEntity", alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
registerFactory("VirtualEntityGroup", alt.VirtualEntityGroup, alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

if (alt.isServer) {
    registerFactory("VoiceChannel", alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);
}

// Factory ctors
alt.PointBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => (ctx.blipType = alt.Enums.BlipType.DESTINATION));

alt.AreaBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => (ctx.blipType = alt.Enums.BlipType.AREA));

alt.RadiusBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => (ctx.blipType = alt.Enums.BlipType.RADIUS));

alt.VirtualEntity.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VIRTUAL_ENTITY);

alt.VirtualEntityGroup.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

alt.ColShape.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE);

alt.ColShapeSphere.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.SPHERE));

alt.ColShapeCylinder.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CYLINDER));

alt.ColShapeCircle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CIRCLE));

alt.ColShapeCuboid.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.CUBOID));

alt.ColShapeRectangle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.RECTANGLE));

alt.ColShapePolygon.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => (ctx.colShapeType = alt.Enums.ColShapeType.POLYGON));

alt.Checkpoint.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.CHECKPOINT);

if (alt.isServer) {
    alt.VoiceChannel.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VOICE_CHANNEL);
}

// Helpers
function setEntityFactory(altClass, type) {
    return (factory) => {
        assert(typeof factory === "function" && altClass.isPrototypeOf(factory), `Factory has to inherit from alt.${altClass.name}`);
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

export function getFactoryCreateFunction(type, ctxCb) {
    return (ctx) => {
        assertIsObject(ctx, "Invalid args");
        if (ctxCb) ctxCb(ctx);
        return cppBindings.createEntity(type, ctx);
    };
}
