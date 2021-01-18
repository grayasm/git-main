/* Cap.4 Expressions and Operators
   4.5 Invocation Expressions

   $ node 05_expr_invocation.js

   An invocation expression is JavaScript's syntax for calling a function or
   method.
*/

var x = 3, y = 1, z = -1;
var m = Math.max(x, y, z);
console.log(m); // 3

var a = [ 10.1, 0.101, -101];
a.sort();
console.log(a); // [ -101, 0.101, 10.1 ]
