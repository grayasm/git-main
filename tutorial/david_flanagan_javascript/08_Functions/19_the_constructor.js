/* Cap.8
   8.7.6 The Function() Constructor

   $ node 19_the_constructor.js

   Functions are usually defined using the function keyword, but can also
   be defined with the Function() constructor.
*/

var f = new Function("x", "y", "return x*y;");
console.log( f(2,3) );  // => 6
