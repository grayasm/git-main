/* Cap.7 Arrays
   7.11 Array-Like Objects

   $ node 24_object_as_array.js

   JavaScript arrays have some special features:
   - the length property is automatically updated as new elements are added
   - setting the length to a smaller value truncates the array
   - Array inherits useful methods from Array.prototype
   - Array has a class attribute of "Array"

   Although you cannot invoke Array methods on objects, some objects behave like
   Arrays in practice.
*/


var a = { };                // Start with a regular empty object.
var i = 0;
while (i < 10) {
    a[i] = i*i;             // Add properties to make it "array-like"
    i++
}
a.length = i;


var total = 0;
for(var j = 0; j < a.length; j++)   // Now iterate through it as if it were a real array
    total += a[j];

console.log(total);         // => 285


// How to write a method that test if an Object is like an Array:
function isArrayLike(o) {
    if (o &&                                    // o is not null, undefined, etc
        typeof o === "object" &&                // o is an object
        isFinite(o.length) &&                   // o.length is a finite number
        o.length >= 0 &&                        // o.length is non-negative
        o.length === Math.floor(o.length) &&    // o.length is an integer
        o.length < 424967296)                   // o.length < 2^32
        return true;                            // Then o is Array like
    else
        return false;                           // Otherwise it is not.
}

console.log(isArrayLike(a));         // => true
console.log(isArrayLike(total));     // => false


// How to use Array methods on Objects
var a = { "0":"a", "1":"b", "2":"c", length:3}; // An array-like object
Array.prototype.join.call(a, "+");              // => "a+b+c"
Array.prototype.slice.call(a, 0);               // => ["a","b","c"], true array copy
