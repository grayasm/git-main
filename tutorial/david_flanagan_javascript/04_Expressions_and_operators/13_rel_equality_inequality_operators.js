/* Cap.4 Expressions and Operators
   4.9.1 Equality and Inequality Operators

   $ node 13_rel_equality_inequality_operators.js

   ==   Equal
   ===  Strictly equal
   !=   Inequality operator   (opposite of ==)
   !==  Strictly inequality operator (opposite of ===)
*/


// The strict equality operator (===)
console.log( 1 === "1" );      // false: not the same type; no conversion;
console.log(null === null);    // true
console.log(undefined === undefined); // true
console.log(true === true);    // true
console.log(false === false);  // true
console.log(0 === NaN);        // false    NaN is never equal with anything
console.log(NaN === NaN);      // false
console.log(NaN !== NaN);      // true: check if value is NaN
console.log(-01234 === -01234);// true
console.log(0 === -0);         // true
console.log("NaN" === "NaN");  // true
console.log("µV" === "μV");    // false: visually equal but with different Unicode encoding
console.log("\u03BC" + "V");   // Greek small letter mu: μ
console.log("\u00B5" + "V");   // Electronics, micro sign: µ


// The equality operator (==) is less strict.
console.log( 1 == "1" );       // true: different types, but equal after conversion
console.log(null == undefined);// true: null is equal with undefined
console.log( "10" == 10 );     // true: equal after conversion
console.log( 1 == true );      // true: convert true -> 1
console.log( false == 0 );     // true: convert false -> 0
console.log( typeof {} == "object" ); // true
