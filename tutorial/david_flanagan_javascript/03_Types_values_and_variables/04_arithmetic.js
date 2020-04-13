/* Cap.3 Types, Values and Variables
   3.1.3 Arithmetic in JavaScript

   The language provides the usual arithmetic operators: + - * / and % (modulo).
   Additionally the Math object provides methods and properties.
   JavaScript does not rise erros for overlow, underflow or division by zero.

   Overflow: the result is larger than the largest representable number.
             It will be printed as Infinity or -Infinity.
             Any operation with Infinity will have infinity as result.

   Underflow: the result is closer to zero than the smallest representable
              number. It will print 0 or -0 special "negative zero".

   Division by zero: the result is Infinity or -Infinity.
                     0 / 0 result is the special not-a-number printed NaN.
                     Infinity / Infinity result is also a NaN.
                     Math.sqrt(-4) result is also NaN.
                     2 / 'a' result is also NaN.

  Infinity and NaN are global variables.
  The Number object defines alternatives, see example.
*/

Infinity;                           // Infinity
Number.POSITIVE_INFINITY;           // Infinity
1/0;                                // Infinity
Number.MAX_VALUE + 1;               // 1.7976931348623157e+308 (Chrome,x86_64)

Number.NEGATIVE_INFINITY;           // -Infinity
-Infinity;                          // -Infinity
-1/0;                               // -Infinity
-Number.MAX_VALUE - 1;              // -1.7976931348623157e+308 (Chrome,x86_64)


NaN;                                // NaN
Number.NaN;                         // NaN
0/0;                                // NaN


Number.MIN_VALUE / 2;               // 0
-Number.MIN_VALUE / 2;              // -0
-1 / Infinity;                      // -0
-0;                                 // -0


var nanval = 0/0;                   // NaN , to test if x is NaN use x != x;
nanval != nanval;                   // true
isNaN(nanval);                      // true

isFinite(nanval);                   // false, arg is not a NaN or +/-Inifinity

var zero = 0;                       // zero
var negz = -0;                      // negative zero

zero === negz;                      // true , zero is equal w/ zegative zero
1/zero === 1/negz;                  // false, infinity is not equal w/ -infinity
