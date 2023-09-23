/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/shared";

/** @type {typeof import("../utils/events.js")} */
const { registerEventHandler } = requireBinding("shared/compatibility/utils/events.js");

registerEventHandler(alt.Enums.EventType.CREATE_BASE_OBJECT_EVENT, "baseObjectCreate", ({ object }) => {
    return [object];
});

registerEventHandler(alt.Enums.EventType.REMOVE_BASE_OBJECT_EVENT, "baseObjectRemove", ({ object }) => {
    return [object];
});

registerEventHandler(alt.Enums.EventType.NETOWNER_CHANGE, "netOwnerChange", ({ entity, oldOwner, newOwner }) => {
    return [entity, newOwner, oldOwner];
});

registerEventHandler(alt.Enums.EventType.WEAPON_DAMAGE_EVENT, "weaponDamage", ({ source, target, weaponHash, damage, offset, bodyPart }) => {
    return [source, target, weaponHash, damage, offset, bodyPart];
});
