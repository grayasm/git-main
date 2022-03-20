/* Cap.7 Arrays
   7.9.2 map()

   $ node 18_ecma5__map.js

   Array.map() passes each element of the array to the function you specify,
   and returns an array containing the values returned by that function.
*/


a = [1, 2, 3];
b = a.map(function(x) { return x*x; });  // b is [1,4,9]

console.log('a=' + a);   // => [1, 2, 3]
console.log('b=' + b);   // => [1, 4, 9]
