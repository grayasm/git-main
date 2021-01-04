/* Cap.3 Types, Values and Variables
   3.8.2. Explicit Conversions

   $ node 18_explicit_conversions.js

   - the simples way to perform an explicit conversion is to use functions:
         new Boolean()
         new Number()
         new String()
         new Object()
   - null and undefined cannot be converted to objects (throws TypeError)
   - binary operator + performs implicit type conversion
   - unary  operator ! converts its operand to a boolean and negates it

     Certain idoms have emerged by using these operators:
     x + ""     same as String(x)
     +x         same as Number(x)
     x-0        same as Number(x)
     !!x        same as Boolean(x) ; note double !
*/


/*    Number.toString()
      Number.toString(radix)

      Converts a number object to string using an optional argument as radix,
      or base for the conversion. If not specified, base 10 is used.
*/
var n = 17;
binary_string = n.toString(2);
octal_string = "0" + n.toString(8);
hex_string = "0x" + n.toString(16);

console.log(binary_string);       // 10001
console.log(octal_string);        // 021
console.log(hex_string);          // 0x11


/*    Number.toFixed(precision)

      Converts a number to a string with a specified number of digits after
      the decimal point. It never uses the exponential notation.
*/
var n = 123456.789;
console.log(n.toFixed(0));        // 123457
console.log(n.toFixed(2));        // 123456.79
console.log(n.toFixed(5));        // 123456.78900

/*    Number.toExponential(precision)

      Converts a number to a string using the exponential notation, with one
      digit before the decimal point and a specified number of digits after
      the decimal point.
*/

console.log(n.toExponential(1));  // 1.2e+5
console.log(n.toExponential(3));  // 1.235e+5


/*    Number.toPrecision(digits)

      Converts a number to a string with the number of significant digits you
      specify. It uses the exponential notation if the number of significant
      digits is not large enough to display the entire integer portion of the
      number.
*/
console.log(n.toPrecision(4));    // 1.235e+5
console.log(n.toPrecision(7));    // 123456.8
console.log(n.toPrecision(10));   // 123456.7890


/*    parseInt(s)
      parseInt(s, radix)  ; with radix in [2, 36]
      parseFloat(s)

      - are global functions, not methods of any class
      - skips leading whitespace
      - parse as many numeric characters as they can and ignore anything after
      - if the 1st nonspace is not a numeric literal then it returns NaN
*/

console.log(  parseInt("3 blind mice")  );    // 3
console.log(  parseInt("-12.34")        );    // -12
console.log(  parseInt("0xFF")          );    // 255
console.log(  parseInt("0xff")          );    // 255
console.log(  parseInt("-0XFF")         );    // -255
console.log(  parseInt("0.1")           );    // 0
console.log(  parseInt(".1")            );    // NaN: integers can't start with "."
console.log(  parseInt("$72.47")        );    // NaN: numbers can't start with "$"

console.log(  parseFloat(" 3.14 meters"));    // 3.14
console.log(  parseFloat(".1")          );    // 0.1
console.log(  parseFloat("$72.47")      );    // NaN: number can't start with "$"

console.log(  parseInt("11", 2)         );    // 3 (1*2 + 1)
console.log(  parseInt("ff", 16)        );    // 255 (15*16 + 15)
console.log(  parseInt("zz", 36)        );    // 1295 (35*36 + 35)
console.log(  parseInt("077", 8)        );    // 63 (7*8 + 7)
console.log(  parseInt("077", 10)       );    // 77 (7*10 + 7)
