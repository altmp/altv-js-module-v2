/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/server/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/server";

class Profiler {
    static takeHeapSnapshot() {
        return alt.Profiler.takeHeapSnapshot();
    }
}

cppBindings.registerCompatibilityExport("Profiler", Profiler);
