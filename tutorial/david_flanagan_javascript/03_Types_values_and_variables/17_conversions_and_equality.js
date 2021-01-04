/* Cap.3 Types, Values and Variables
   3.8.1 Conversions and Equality

   $ node 17_conversions_and_equality.js

   ==  flexible equality operator does conversion to determine the result
   === strict equality operator does not perform conversion when testing for eq
*/

var a = (null == undefined);     // true
var b = ("0" == 0);              // true
var c = (0 == false);            // true
var d = ("0" == false);          // true

console.log(a);
console.log(b);
console.log(c);
console.log(d);
