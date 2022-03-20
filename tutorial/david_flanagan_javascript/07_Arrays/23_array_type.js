/* Cap.7 Arrays
   7.10 Array Type

   $ node 23_array_type.js

   Array.isArray() tests and returns true if an object is an array.
*/


Array.isArray([]); // => true
Array.isArray({}); // => false


// How to write our own isArray() method:

var isArray = Function.isArray || function(o) {
    return typeof o === "object" &&
        Object.prototype.toString.call(o) === "[object Array]";
}



var a = [1];
var b = { 1 : 1 };

console.log(isArray(a));  // => true
console.log(isArray(b));  // => false
