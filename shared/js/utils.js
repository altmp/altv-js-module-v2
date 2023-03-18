requireBinding("shared/timers.js");
const { inspect } = requireBinding("shared/logging.js");

alt.Utils.inspect = inspect;

alt.Utils.wait = (ms) => new Promise((resolve) => alt.Timers.setTimeout(resolve, ms));
alt.Utils.waitForNextTick = () => alt.Utils.wait(0);
