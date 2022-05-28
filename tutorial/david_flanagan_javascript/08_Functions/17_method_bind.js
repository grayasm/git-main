/* Cap.8 Functions
   8.7.4 The bind() Method

   $ node 17_method_bind.js

   The primary purpose of bind() is to bind a function to an object.
   When you invoke the bind() method on a function f and pass an object o,
   the method returns a new function. Invoking the new function invokes
   the original function f as a method of o.
*/

function f(y) { return this.x + y; }
var o = { x:1 };
var g = f.bind(o);

console.log( g(2) ); // => 3
