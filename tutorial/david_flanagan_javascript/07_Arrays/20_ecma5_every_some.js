/* Cap.7 Arrays
   7.9.4 every() and some()

   $ node 20_ecma5_every_some.js

   Array.every() returns true if and only if your predicate functions returns
   true for all elements in the array.
*/

a = [1,2,3,4,5];
a.every(function(x) { return x < 10; });   // => true: all values < 10
a.every(function(x) { return x%2===0; });  // => false: not all values even

a.some(function(x) { return x%2===0; });   // => true: some numbers are even
a.some(isNaN)                              // => false: a has no non-numbers
