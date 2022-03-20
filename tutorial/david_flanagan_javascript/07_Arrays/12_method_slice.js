/* Cap.7 Arrays
   7.8.5 slice()

   $ node 12_method_slice.js

   Array.slice() returns a subarray of the specified array.
*/

var a = [1,2,3,4,5];

a.slice(0,3);       // => [1,2,3]
a.slice(3);         // => [4,5]
a.slice(1, -1);     // => [2,3,4]
a.slice(-3,-2);     // => [3]
