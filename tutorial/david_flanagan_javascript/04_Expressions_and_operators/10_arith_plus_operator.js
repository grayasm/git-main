/* Cap.4 Expressions and Operators
   4.8.1 The + Operator

   $ node 10_arith_plus_operator.js
*/


console.log(  1 + 2                  ); // 3
console.log(  "hello" + " " + "there"); // "hello there"
console.log(  "1" + "2"              ); // "12"
console.log(  "1" +  2               ); // "12" concatenation after number-to-string
console.log(  1 + {}                 ); // "1[object Object]": concatenation after object-to-string
console.log(  true + true            ); // 2: addition after boolean-to-number
console.log(  2 + null               ); // 2: addition after null converts to 0
console.log(  2 + undefined          ); // NaN: addition after undefined converts to NaN
console.log(  1 + 2 + " blind mice"  ); // "3 blind mice"
console.log(  1 + (2 + " blind mice")); // "12 blind mice"
