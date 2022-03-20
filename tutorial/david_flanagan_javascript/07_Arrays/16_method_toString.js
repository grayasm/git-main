/* Cap.7 Arrays
   7.8.9 toString() and toLocaleString()

   $ node 16_method_toString.js

   Array.toString() converts each of its elements to a string, and outputs a
   comma separated list of those strings.
*/


[1,2,3].toString();         // => '1,2,3'
["a", "b", "c"].toString(); // => 'a,b,c'
[1, [2, 'c']].toString();   // => '1,2,c'
