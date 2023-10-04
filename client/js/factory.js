/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("Audio", alt.Audio, alt.Enums.BaseObjectType.AUDIO);
registerFactory("AudioFilter", alt.AudioFilter, alt.Enums.BaseObjectType.AUDIO_FILTER);
registerFactory("AudioOutputAttached", alt.AudioOutputAttached, alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);
registerFactory("AudioOutputFrontend", alt.AudioOutputFrontend, alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);
registerFactory("AudioOutputWorld", alt.AudioOutputWorld, alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);

registerFactory("LocalPed", alt.LocalPed, alt.Enums.BaseObjectType.LOCAL_PED);
registerFactory("LocalVehicle", alt.LocalVehicle, alt.Enums.BaseObjectType.LOCAL_VEHICLE);
registerFactory("LocalObject", alt.LocalObject, alt.Enums.BaseObjectType.LOCAL_OBJECT);

registerFactory("RmlDocument", alt.RmlDocument, alt.Enums.BaseObjectType.RML_DOCUMENT);

registerFactory("WebSocketClient", alt.WebSocketClient, alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);

registerFactory("WebView", alt.WebView, alt.Enums.BaseObjectType.WEBVIEW);
registerFactory("TextLabel", alt.TextLabel, alt.Enums.BaseObjectType.TEXT_LABEL);

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
