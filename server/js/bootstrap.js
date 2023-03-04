const alt = process._linkedBinding("alt");

console.log("Bootstrapper loaded");
console.log(alt.test);
alt.test = 42;
console.log(alt.test);
console.log(alt.test2);
