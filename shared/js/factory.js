export function setEntityFactory(altClass, type) {
    return (factory) => {
        if(typeof factory !== 'function' || !altClass.isPrototypeOf(factory)) throw new Error(`Factory has to inherit from alt.${altClass.name}`);
        if(factory.length !== 0) throw new Error(`Factory constructor has to have no arguments`);
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
