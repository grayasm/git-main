/* Cap.4 Expressions and Operators
   4.9.3 The instanceof Operator

   $ node 16_rel_the_instanceof_operator.js

   The instanceof operator expects:
     - left-side operand: object
     - right-side operand: identifies a class of objects
*/

var d = new Date();
console.log( d instanceof Date  );   // true: d was created with Date
console.log( d instanceof Object );  // true: all objects are instances of Object
console.log( d instanceof Number );  // false: d is not a Number object

var a = [1, 2, 3];
console.log( a instanceof Array );   // true: a is an array
console.log( a instanceof Object );  // true: all arrays are objects
console.log( a instanceof RegExp );  // false: arrays are not regular expressions
