/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("Audio", alt.Audio, alt.Enums.BaseObjectType.AUDIO);

// Factory ctors

alt.Audio.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO);

alt.AudioFilter.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_FILTER);

alt.LocalPed.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_PED);

alt.LocalVehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_VEHICLE);

alt.RmlDocument.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.RML_DOCUMENT);

alt.Object.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.OBJECT, (ctx) => (ctx.isWeaponObject = false));

alt.WeaponObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.OBJECT, (ctx) => (ctx.isWeaponObject = true));

alt.WebSocketClient.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);
