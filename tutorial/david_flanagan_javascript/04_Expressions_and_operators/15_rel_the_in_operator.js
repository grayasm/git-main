/* Cap.4 Expressions and Operators
   4.9.3 The in Operator

   $ node 15_rel_the_in_operator.js

   The 'in' operator expects:
     - left side operand: "string" or type that can be converted to string
     - right side operand: object

   It evalues to true if the left-side value is a name of a property of the
   right-side object.
*/


var point = { x:1, y:1 };

console.log( "x" in point );          // true: object has property named "x"
console.log( "z" in point );          // false: object has no property "z"
console.log( "toString" in point);    // true: object inherits toString method

var data = [7, 8, 9];
console.log( "0" in data );           // true: array has an element "0"
console.log( 1 in data );             // true: numbers are converted to strings
console.log( 3 in data );             // false: no element 3
