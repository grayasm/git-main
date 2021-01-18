/* Cap.4 Expressions and Operators
   4.11   Assignment Expressions
   4.11.1 Assignment with Operation

   $ node 20_assignment.js

   JavaScript uses the = operator to assign a value to a variable or property.

   Assignment operators:
  +--------------------------------------------------------------------------+
   Operator      Example       Equivalent
  +--------------------------------------------------------------------------+
    +=           a += b        a = a + b
    -=           a -= b        a = a - b
    *=           a *= b        a = a * b
    /=           a /= b        a = a / b
    %=           a %= b        a = a % b
    <<=          a <<= b       a = a << b
    >>=          a >>= b       a = a >> b
    >>>=         a >>>= b      a = a >>> b
    &=           a &= b        a = a & b
    |=           a |= b        a = a | b
    ^=           a ^= b        a = a ^ b
  +--------------------------------------------------------------------------+
*/

var o = {};
var i = o;        // set the variable i to o
o.x = 1;          // set the property x of the object o to 1

console.log(o);   // { x: 1 }


// Assignment operators with side-effects.
var a1 = [2,4,6];
var a2 = [2,4,6];

var i = j = 0;
a1[i++] *= 2;               // not the same
a2[j++] = a2[j++] * 2;      // as this one

console.log('a1=', a1);     // a1= [4, 4, 6]
console.log('a2=', a2);     // a2= [8, 4, 6]
