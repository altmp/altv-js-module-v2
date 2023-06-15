/** @type {typeof import("../../shared/js/factory.js")} */
const { registerFactory, getFactoryCreateFunction } = requireBinding("shared/factory.js");

registerFactory("Audio", alt.Audio, alt.Enums.BaseObjectType.AUDIO);

// Factory ctors

alt.Audio.create = getFactoryCreateFunction(alt.Enums.BaseObjectType.AUDIO);
