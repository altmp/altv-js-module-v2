/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory(alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);
registerFactory(alt.ConnectionInfo, alt.Enums.BaseObjectType.CONNECTION_INFO);

// Factory ctors
alt.Vehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VEHICLE);

alt.Ped.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.PED);

alt.Object.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.OBJECT);

alt.VoiceChannel.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VOICE_CHANNEL);
