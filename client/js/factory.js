/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory(alt.Audio, alt.Enums.BaseObjectType.AUDIO);
registerFactory(alt.AudioFilter, alt.Enums.BaseObjectType.AUDIO_FILTER);
registerFactory(alt.AudioOutputAttached, alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);
registerFactory(alt.AudioOutputFrontend, alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);
registerFactory(alt.AudioOutputWorld, alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);

registerFactory(alt.LocalPlayer, alt.Enums.BaseObjectType.LOCAL_PLAYER);
registerFactory(alt.LocalPed, alt.Enums.BaseObjectType.LOCAL_PED);
registerFactory(alt.LocalVehicle, alt.Enums.BaseObjectType.LOCAL_VEHICLE);
registerFactory(alt.LocalObject, alt.Enums.BaseObjectType.LOCAL_OBJECT);

registerFactory(alt.RmlDocument, alt.Enums.BaseObjectType.RML_DOCUMENT);

registerFactory(alt.WebSocketClient, alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);

registerFactory(alt.WebView, alt.Enums.BaseObjectType.WEBVIEW);
registerFactory(alt.TextLabel, alt.Enums.BaseObjectType.TEXT_LABEL);

// Factory ctors

alt.Audio.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO);

alt.AudioFilter.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_FILTER);

alt.AudioOutputAttached.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);

alt.AudioOutputFrontend.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);

alt.AudioOutputWorld.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);

alt.LocalPed.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_PED);

alt.LocalVehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_VEHICLE);

alt.LocalObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_OBJECT, (ctx) => (ctx.isWeaponObject = false));

alt.RmlDocument.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.RML_DOCUMENT);

alt.WeaponObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_OBJECT, (ctx) => (ctx.isWeaponObject = true));

alt.WebSocketClient.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);

alt.WebView.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.WEBVIEW);

alt.TextLabel.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.TEXT_LABEL);
