/* Cap.6 Objects
   6.10.1 The toString() Method

   $ node 19_method_toString.js


   The toString() method takes no arguments; it returns a string that somehow
   represents the value of the object on which it is invoked.

   Reference:
   Object.toString()
   Array.toString()
   Date.toString()
   Function.toString()
*/

var s = { x:1, y:1 }.toString();

console.log(s);     // [object Object]
