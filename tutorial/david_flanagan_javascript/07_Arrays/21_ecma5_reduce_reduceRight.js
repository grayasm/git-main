/* Cap.7 Arrays
   7.9.5 reduce() and reduceRight()

   $ node 21_ecma5_reduce_reduceRight.js

   Array.reduce() combines the elements of an array, using the function you
   specify to produce a single value.

   Array.reduceRight() is just like reduce() except is processes the array
   from its highest index to lowest (right-to-left).
*/

var a = [1,2,3,4,5];
var sum = a.reduce(function(x,y) { return x + y; }, 0); // Sum of values
var prod = a.reduce(function(x,y) { return x*y; }, 1);  // Product of values
var max = a.reduce(function(x,y) { return (x>y)?x:y; });// Largest value

// => sum=15   prod=120  max=5


var a = [2,3,4];
// Compute 2^(3^4). Exponentionation has right-to-left precedence.
var big = a.reduceRight(function(accumulator,value) {
    return Math.pow(value,accumulator);
});
console.log(big);  // => 2.4178516392292583e+24
