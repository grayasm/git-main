/* Cap.4 Expressions and Operators
   4.8.2 Unary Arithmetic Operators

   $ node 11_arith_unary_operators.js

   Unary plus  (+)
   Unary minus (-)
   Increment   (++)
   Decrement   (--)
*/

var i = 1, j = ++i;
console.log('i=', i , 'j=', j);     // i=2  j=2

var p = 1, q = p++;
console.log('p=', p, ' q=', q);     // p=2  q=1

var x = "1";
console.log( 'x=', ++x );           // x=2
console.log( 'x+1=', x + 1);        // x+1=3
