/* Cap.4 Expressions and Operators
   4.7.6 Operator Associativity

   $ node 09_op_associativity.js

   L specifies left-to-right associativity
   R specifies right-to-left associativity
*/

// --- Example for L (left-to-right) ---
var w = 10 - 3 - 2;
var w = ((10 - 3) - 2);
console.log('w=', w);           // w=5



// --- Example for R (right-to-left) ---
var x = ~-10;
console.log('x=', x);           // x=9

var w = x = y = z = 5;
console.log('x=', x);           // x=5

var a = b = c = d = e = f = 0;
var g = 10;

var q = a ? b : c ? d : e ? f : g;
console.log('q=', q);           // q=10
