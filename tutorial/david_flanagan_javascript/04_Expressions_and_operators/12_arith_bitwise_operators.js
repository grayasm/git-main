/* Cap.4 Expressions and Operators
   4.8.3 Bitwise Operators

   $ node 12_arith_bitwise_operators.js

   Bitwise AND  &
   Bitwise OR   |
   Bitwise XOR  ^
   Bitwise NOT  ~
   Shift left   <<
   Shift right with sign      >>
   Shift right with zero fill >>>
*/


console.log(  0x1234 & 0x00FF  );  // 0x0034 = 52 (base10)
console.log(  0x1234 | 0x00FF  );  // 0x12ff = 4863 (base10)
console.log(  0xff00 ^ 0xf0f0  );  // 0x0ff0 = 4080 (base10)
console.log(  ~0x0f            );  // 0xfffffff0 = -16 (base10)
console.log(  7 << 2           );  // 28 (base10) (2 times left shift = *2*2)
console.log(  7 >> 1           );  // 3 (base10)
console.log( -7 >> 1           );  // -4 (base10)  (keeps the leftmost sign bit)
console.log( -1 >>> 4          );  // 268435455 = 0x0fffffff
