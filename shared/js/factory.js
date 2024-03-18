/** @type {typeof import("./utils.js")} */
const { assert, assertIsObject } = requireBinding("shared/utils.js");

registerFactory(alt.Player, alt.Enums.BaseObjectType.PLAYER);
registerFactory(alt.Vehicle, alt.Enums.BaseObjectType.VEHICLE);
registerFactory(alt.Ped, alt.Enums.BaseObjectType.PED);
registerFactory(alt.Blip, alt.Enums.BaseObjectType.BLIP);
registerFactory(alt.Marker, alt.Enums.BaseObjectType.MARKER);
registerFactory(alt.ColShape, alt.Enums.BaseObjectType.COLSHAPE);
registerFactory(alt.Object, alt.Enums.BaseObjectType.OBJECT);
registerFactory(alt.Checkpoint, alt.Enums.BaseObjectType.CHECKPOINT);
registerFactory(alt.VirtualEntity, alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
registerFactory(alt.VirtualEntityGroup, alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

// Factory ctors
alt.PointBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => ({ ...ctx, blipType: alt.Enums.BlipType.DESTINATION }));
alt.AreaBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => ({ ...ctx, blipType: alt.Enums.BlipType.AREA }));
alt.RadiusBlip.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.BLIP, (ctx) => ({ ...ctx, blipType: alt.Enums.BlipType.RADIUS }));

alt.Marker.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.MARKER);

alt.VirtualEntity.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VIRTUAL_ENTITY);
alt.VirtualEntityGroup.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);

alt.ColShape.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE);
alt.ColShapeSphere.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.SPHERE }));
alt.ColShapeCylinder.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.CYLINDER }));
alt.ColShapeCircle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.CIRCLE }));
alt.ColShapeCuboid.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.CUBOID }));
alt.ColShapeRectangle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.RECTANGLE }));
alt.ColShapePolygon.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.COLSHAPE, (ctx) => ({ ...ctx, colShapeType: alt.Enums.ColShapeType.POLYGON }));

alt.Checkpoint.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.CHECKPOINT);

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

export function registerFactory(altClass, type) {
    altClass.setFactory = setEntityFactory(altClass, type);
    altClass.getFactory = getEntityFactory(type);
}

export function getFactoryCreateFunction(type, ctxCb) {
    return (ctx) => {
        if (ctxCb) ctx = ctxCb(ctx);
        assertIsObject(ctx, "Invalid args");

        return cppBindings.createEntity(type, ctx);
    };
}
