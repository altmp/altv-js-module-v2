/// <reference path="../../../../types/shared/index.d.ts" />
/// <reference path="../../../../types/client/index.d.ts" />
// import * as alt from "@altv/client";

requireBinding("shared/entity.js");

/** @type {typeof import("../../../../shared/js/utils.js")} */
const { isVector3 } = requireBinding("shared/utils.js");

class FocusData {
    static overrideFocus(value, focusOffset) {
        if (isVector3(value)) {
            focusOffset ??= { x: 0, y: 0, z: 0 };

            alt.FocusData.focusOverridePos = value;
            alt.FocusData.focusOverrideOffset = focusOffset;
            return;
        }

        alt.FocusData.focusOverrideEntity = value;
    }

    static clearFocus() {
        alt.FocusData.clearFocusOverride();
    }
}

cppBindings.registerCompatibilityExport("FocusData", FocusData);
