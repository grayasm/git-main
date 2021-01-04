/* Cap.3 Types, Values and Variables
   3.5 The Global Object

   When the JavaScript interpreter starts (web browser loads a new page)
   it creates a new global object and gives it an initial set of:
       - global properties like: undefined, Inifinity, NaN, ...
       - global functions like:  isNaN(), parseInt(), eval(), ...
       - constructor functions:  Date(), RegExp(), String(), Object(), Array()
       - global objects like:    Math and JSON.

   Browsers define the Window object as global.
   Node.js defines the Global object as global.
   It contains:
       - core global properties
       - web browser specific properties (if a browser)
       - program defined globals
*/


var global = this;
console.log(global.toString());    // [object Window] <-- in a browser


var v = window;
console.log(v.toString());         // [object Window] <-- in a browser

// Open Linux terminal, type "node" to open interactive js interpreter, then:
var g = global;
console.log(g);                    // Object [global]

/*
Object [global] {
  global: [Circular],
  clearInterval: [Function: clearInterval],
  clearTimeout: [Function: clearTimeout],
  setInterval: [Function: setInterval],
  setTimeout: [Function: setTimeout] {
    [Symbol(nodejs.util.promisify.custom)]: [Function]
  },
  queueMicrotask: [Function: queueMicrotask],
  clearImmediate: [Function: clearImmediate],
  setImmediate: [Function: setImmediate] {
    [Symbol(nodejs.util.promisify.custom)]: [Function]
  },
  g: [Circular]
}
*/
