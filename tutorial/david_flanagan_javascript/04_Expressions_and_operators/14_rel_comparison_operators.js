/* Cap.4 Expressions and Operators
   4.9.2 Comparison Operators

   $ node 14_rel_comparison_operators.js

   Less than <
   Greater than >
   Less than or equal <=
   Greater than or equal >=
*/


console.log(  11 < 3  );    // false: numeric comparison
console.log( "11" < "3" );  // true: string comparison
console.log( "11" < 3 );    // false: numeric comparison
console.log( "one" < 3 );   // false: "one" converted to NaN; numeric comparison
