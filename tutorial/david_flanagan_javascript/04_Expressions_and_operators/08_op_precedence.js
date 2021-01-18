/* Cap.4 Expressions and Operators
   4.7.5 Operator Precedence

   $ node 08_op_precedence.js

   The table in 07_op_overview.js lists the operators in order from high preced
   to low precedence, with horizontal lines separating groups of operators at
   the same precedence level.
*/


// Multiplication * has higher precedence than the addition +
// Assignment = has the lowest precedence
var r = 10 + 2*3;
console.log('r=', r); // r=16

// Op precedence can be overwritten with the explicit use of parantheses ( )
var r = (10 + 2)*3;
console.log('r=', r); // r=36
