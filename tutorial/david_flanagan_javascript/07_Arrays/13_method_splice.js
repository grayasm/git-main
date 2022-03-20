/* Cap.7 Arrays
   7.8.6 splice()

   $ node 13_method_splice.js

   Array.splice() can delete elements from an array, insert new elements into
   an array, or perform both operatins at the same time.
*/


var a = [1,2,3,4,5,6,7,8];

a.splice(4);    // Returns [5,6,7,8]; a is [1,2,3,4]
a.splice(1,2);  // Returns [2,3]; a is [1,4]
a.splice(1,1);  // Returns [4]; a is [1]

// Inserting new elements
var a = [1,2,3,4,5];
a.splice(2,0,'a','b');   // Returns []; a is [1,2,'a','b',3,4,5]
a.splice(2,2,[1,2],3);   // Returns ['a','b']; a is [1,2,[1,2],3,3,4,5]
