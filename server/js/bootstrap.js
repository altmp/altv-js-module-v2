const alt = process._linkedBinding("alt");

console.log("Bootstrapper loaded");
console.log(alt.test);
alt.test = 45;
console.log(alt.test);
console.log(alt.test2);
console.log(alt.Player.shared);
