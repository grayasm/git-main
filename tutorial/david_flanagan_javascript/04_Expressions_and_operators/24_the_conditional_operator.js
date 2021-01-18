/* Cap.4 Expressions and Operators
   4.13.1 The Conditional Operator (?:)

   $ node 24_the_conditional_operator.js

   The ternary operator ?:
   The same description as in C:
     - the first operand is boolean (or converted to)
     - if "truthy" the second value is returned
     - if "falsy" the 3rd value is returned

   x > 0 ? x : -x
*/

var username = undefined;
var greeting = "hello " + (username ? username : "there");

console.log( greeting );  // "hello there"
