/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("Audio", alt.Audio, alt.Enums.BaseObjectType.AUDIO);
registerFactory("WebView", alt.WebView, alt.Enums.BaseObjectType.WEBVIEW);

// Factory ctors

alt.Audio.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO);

alt.AudioFilter.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_FILTER);

alt.AudioOutputAttached.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_ATTACHED);

alt.AudioOutputFrontend.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_FRONTEND);

alt.AudioOutputWorld.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_OUTPUT_WORLD);

alt.LocalPed.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_PED);

alt.LocalVehicle.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_VEHICLE);

alt.RmlDocument.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.RML_DOCUMENT);

alt.LocalObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_OBJECT, (ctx) => (ctx.isWeaponObject = false));

alt.WeaponObject.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.LOCAL_OBJECT, (ctx) => (ctx.isWeaponObject = true));

alt.WebSocketClient.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.WEBSOCKET_CLIENT);

alt.WebView.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.WEBVIEW);
