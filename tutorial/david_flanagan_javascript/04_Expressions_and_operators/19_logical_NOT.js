/* Cap.4 Expressions and Operators
   4.10.3 Logical NOT (!)

   $ node 19_logical_NOT.js

   It's purpose is to invert the boolean value of its operand.
*/

var p = true, q = false;

console.log(  !(p && q)  );  // true, similar with next one
console.log(  !p || !q   );  // true

console.log(  !(p || q)  );  // false, similar with next one
console.log(  !p && !q   );  // false
