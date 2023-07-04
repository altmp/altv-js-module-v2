/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("VoiceChannel", alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);

// Factory ctors
alt.Vehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VEHICLE);

alt.Ped.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.PED);

alt.NetworkObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.NETWORK_OBJECT);

alt.VoiceChannel.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.VOICE_CHANNEL);
