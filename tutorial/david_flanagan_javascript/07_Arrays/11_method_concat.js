/* Cap.7 Arrays
   7.8.4 concat()

   $ node 11_method_concat.js

   Array.concat() creates and returns a new array where the arguments are
   concatenated at the end of given array.
*/

var a = [1, 2, 3];
a.concat(4, 5);          // => [1,2,3,4,5]
a.concat([4, 5]);        // => [1,2,3,4,5]
a.concat([4,5], [6,7]);  // => [1,2,3,4,5,6,7]
a.concat(4, [5, [6,7]]); // => [1,2,3,4,5,[6,7]]
