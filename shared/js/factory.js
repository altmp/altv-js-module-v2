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

alt.Factory.getPlayerFactory = getEntityFactory(alt.Enums.BaseObjectType.PLAYER);
alt.Factory.getVehicleFactory = getEntityFactory(alt.Enums.BaseObjectType.VEHICLE);

// Factory ctors
alt.Vehicle.create = (ctx) => {
    if(typeof ctx !== "object") throw new Error("Invalid args");

    let { model, pos, rot } = ctx;
    if(typeof model !== "number" && typeof model !== "string") throw new Error("Invalid model arg");
    if(typeof pos !== "object" || !(pos instanceof alt.Vector3)) throw new Error("Invalid pos arg");
    if(typeof rot !== "object" || !(rot instanceof alt.Vector3)) rot = new alt.Vector3(0, 0, 0);

    let modelHash = 0;
    if(typeof model === "number") modelHash = model;
    else if(typeof model === "string") modelHash = alt.hash(model);

    return cppBindings.createEntity(alt.Enums.BaseObjectType.VEHICLE, modelHash, pos, rot);
};
