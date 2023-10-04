/*** @type {typeof import("../../shared/js/utils.js")} */
const { waitFor } = requireBinding("shared/utils.js");

alt.LocalObject.prototype.waitForSpawn = function (timeout = 2_000) {
    return waitFor(() => this.scriptID !== 0, timeout);
};

alt.LocalVehicle.prototype.waitForSpawn = function (timeout = 2_000) {
    return waitFor(() => this.scriptID !== 0, timeout);
};

alt.LocalPed.prototype.waitForSpawn = function (timeout = 2_000) {
    return waitFor(() => this.scriptID !== 0, timeout);
};
