/* Cap.3 Types, Values and Variables
   3.1   Numbers

   JavaScript numbers are 64-bit floating-point as defined by IEEE 754 standard.
   Large value +/-1.7976931348623157 x 10^308
   Small value +/-5 x 10^(-324)

   JavaScript format allows to represent integers with
   Maxim value +9007199254740992 as +2^53
   Minim value -9007199254740992 as -2^53

   If you use integers values larger that this, you will loose precision in
   the trailing digits.

   Array indexing and bitwise operators are performed with 32-bit integers.
   This limits are valid also on 32bit platforms like Mozilla on linux i686.
*/

var num1 = -1.7976931348623157 * Math.pow(10,308); // -1.7976931348623157e+308
var num2 = +1.7976931348623157 * Math.pow(10,308); // 1.7976931348623157e+308

var num3 = -5 * Math.pow(10,-324); // -0
var num4 = +5 * Math.pow(10,-324); // 0

var num5 = Math.pow(+2,53); // 9007199254740992
var num6 = Math.pow(-2,53); //-9007199254740992

console.log(num1);
console.log(num2);
console.log(num3);
console.log(num4);
console.log(num5);
console.log(num6);

// Interesting fact about num3 and num4.
Math.pow(10,-323) * 0.5;   // 5e-234
Math.pow(10,-324);         // 0
Math.pow(10,-234) * 5;     // 0
Math.pow(10,-323) * 0.3;   // 5e-234 ->it cannot be represented anymore
Math.pow(10,-323) * 0.2;   // 0
