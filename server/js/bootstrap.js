// clang-format off
const alt = process._linkedBinding("alt");

alt.log("Bootstrapper loaded");

alt.Events.onResourceStart(({ resourceName }) => {
    alt.log(`Resource ${resourceName} started`);
});

alt.Events.onResourceStop(({ resourceName }) => {
    alt.log(`Resource ${resourceName} stopped`);
});

alt.Events.on("test", (arg) => {
    alt.log("got test: " + arg);
});

let vector = new Vector3(8, 5, 3);
alt.log(vector.x);

/*
console.log(alt.test);
alt.test = 45;
console.log(alt.test);
console.log(alt.test2);
console.log(alt.Player.shared);

let player = new alt.Player("testabc", 23);
let player2 = new alt.Player(23, "testabc");

let vehicle = new alt.Vehicle("t20");
console.log("vehicle 1:", vehicle.getID(), vehicle.getModel(), vehicle.model);

let vehicle2 = new alt.Vehicle(0x6322B39A);
console.log("vehicle 2:", vehicle.getID(), vehicle.getModel(), vehicle.model);

const interval = new alt.Timers.Interval(1000, () => {console.log("yep cock")});
alt.log(alt.Timers.Interval);
*/
