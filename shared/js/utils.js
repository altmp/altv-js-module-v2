// clang-format off
getBinding("shared/timers.js");

alt.Utils.wait = (ms) => new Promise((resolve) => alt.Timers.setTimeout(resolve, ms));
alt.Utils.waitForNextTick = () => alt.Utils.wait(0);
