/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

// requireBinding("shared/entity.js");

class Resource extends alt.Resource {
    get valid() {
        return !!alt.Resource.get(super.name);
    }

    static getByName(name) {
        return alt.Resource.get(name);
    }
}

cppBindings.registerCompatibilityExport("Resource", Resource);
