/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("Audio", alt.Audio, alt.Enums.BaseObjectType.AUDIO);

// Factory ctors

alt.Audio.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO);

alt.AudioFilter.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO_FILTER);

alt.LocalPed.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.PED);
