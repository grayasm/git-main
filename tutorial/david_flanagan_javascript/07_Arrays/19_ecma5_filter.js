/* Cap.7 Arrays
   7.9.3 filter()

   $ node 19_ecma5_filter.js

   Array.filter() returns an array containing a subset of the elements of the
   array on which it is invoked. It take a predicate function as parameter
   which returns true or false.
*/


var a = [5,4,3,2,1];
smallvalues = a.filter(function(x) { return x < 3; });   // => [2, 1]
everyother = a.filter(function(x,i) { return i%2==0; }); // => [5,3,1]


// filter() skips missing elements in sparse array. Its return value is alway dense.
var sparse = [1,2,3,4,5]
delete sparse[2];
var dense = sparse.filter(function() { return true; }); // => [1,2,4,5]

// How to close gaps and remove undefined and null elements with filter():
var a = [1,2,3,4,5,null,null,undefined];     // a.length = 8
delete a[2];                                 // a.length = 8

a = a.filter(function(x) { return x!== undefined && x != null; });
console.log(a);                              // => [1,2,4,5]
