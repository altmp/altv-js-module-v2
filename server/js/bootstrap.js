const alt = process._linkedBinding("alt");

console.log("Bootstrapper loaded");
/*
console.log(alt.test);
alt.test = 45;
console.log(alt.test);
console.log(alt.test2);
console.log(alt.Player.shared);

let player = new alt.Player("testabc", 23);
let player2 = new alt.Player(23, "testabc");
*/

let vehicle = new alt.Vehicle("t20");
console.log("vehicle 1:", vehicle.getID(), vehicle.getModel(), vehicle.model);

let vehicle2 = new alt.Vehicle(0x6322B39A);
console.log("vehicle 2:", vehicle.getID(), vehicle.getModel(), vehicle.model);
