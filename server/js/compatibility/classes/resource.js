/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
// import * as alt from "@altv/server";

requireBinding("shared/entity.js");

class Resource extends alt.Resource {
    static getByName(name) {
        return alt.Resource.get(name);
    }

    get valid() {
        // TODO (xLuxy): This might be wrong - asuming resource is ALWAYS valid
        return true;
    }
}

cppBindings.registerCompatibilityExport("Resource", Resource);
