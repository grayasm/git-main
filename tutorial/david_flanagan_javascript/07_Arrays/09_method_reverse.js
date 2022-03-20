/* Cap.7 Arrays
   7.8.2 reverse()

   $ node 09_method_reverse.js

   Array.reverse() method reverses the order of the elements of an array
   in place and returns the reversed array.
*/

var a = [1, 2, 3];
a.reverse().join(); // => "3,2,1" and a is now [3, 2, 1]
