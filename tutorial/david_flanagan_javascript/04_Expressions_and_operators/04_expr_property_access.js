/* Cap.4 Expressions and Operators
   4.4 Property Access Expressions

   $ node 04_expr_property_access.js

   JavaScript defines 2 syntaxes for the property access:
   expression . identifier
   expression [ expression ]
*/


var o = { x:1, y: {z:3}};   // An example object
var a = [o, 4, [5, 6]];     // An example array that contains the object

console.log(o.x);           // 1
console.log(o.y.z);         // 3
console.log(o["x"]);        // 1
console.log(a[1]);          // 4
console.log(a[2]["1"]);     // 6
console.log(a[0].x);        // 1
