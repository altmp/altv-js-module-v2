/** @type {typeof import("../../shared/js/entity.js")} */
const { addAllGetter } = requireBinding("shared/entity.js");

addAllGetter(alt.VoiceChannel, alt.Enums.BaseObjectType.VOICE_CHANNEL);
addAllGetter(alt.VirtualEntityGroup, alt.Enums.BaseObjectType.VIRTUAL_ENTITY_GROUP);
