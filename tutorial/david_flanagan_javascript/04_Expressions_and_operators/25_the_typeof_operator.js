/* Cap.4 Expressions and Operators
   4.13.2 The typeof Operator

   $ node 25_the_typeof_operator.js

   typeof is a unary operator with an operand of any type.

  +----------------------------------------------------+
   x                                typeof x
  +----------------------------------------------------+
   undefined                        "undefined"
   null                             "object"
   true or false                    "boolean"
   any number or NaN                "number"
   any string                       "string"
   any function                     "function"
   any nonfunction native object    "object"
   any host object                  An implementation-defined string, but not
                                    "undefined", "boolean", "number" or "string"
  +----------------------------------------------------+
*/

var value = "Cádiz in Spain";
var s = (typeof value == "string") ? "'" + value + "'" : value;

console.log( s );  // 'Cádiz in Spain'
