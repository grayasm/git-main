================================================================================
 Cap.4 Expressions and Operators
================================================================================

    1. Primary expressions:
       1.23; "hello"; /pattern; true; false; null; this; var i, sum;

    2. Array initializer:
       var a = [1, 2, 3];
       var matrix = [[1,2,3], [4,5,6], [7,8,9]];
       var sparse = [1,,,,5];

    3. Object initializer:
       var p = { x:10, y:10 };
       p.x = -10;
       p.y = -10;   // change existing property's value
       p.z = 100;   // add new property

       var rectangle = { upperLeft:  { x:2, y:2 },
                         lowerRight: { x:4, y:5 }};

    4. Function definition:
       var square = function(x) { return x * x; }

    5. Object property access:
       var o = { x:1 , y: {z:3} };
       var a = [o, 4, [5, 6]];

       o.y.z;      // is 3
       o["x"]      // is 1
       a[2]["1"];  // is 6
       a[0].x;     // is 1

    6. Create an object:
       var date = new Date(); // 2021-01-10T17:18:21.240Z

    7. JavaScripts supports the same operators as in C:

       ++ -- - + ~ ! delete typeof void
       * / %      : multiply, divide, remainder
       << >> >>>  : >>> extra in JS, shift right with 0 padding to left
       < <= > >=  : comparison operators
       instanceof : test object class
       in         : test whether property exists
       == != === !== : equality, inequality, strict equality, strict inequality
       & ^ |      : bitwise AND, XOR, OR
       && || ?:   : logical AND, OR and ternary operator ?:
       =          : assign
       *= /= %=   : operate and assign
       -= +=
       &= ^= |=
       <<= >>= >>>=
       ,          : discard first operand, return second.

    8. Operator precedence: higher to lower, can overwrite it by using (  )
    9. Operator associativity:
       > left-to-right var w = 10 - 3 - 2;
       > right-to-left var q = a ? b : c ? d : e;

   10. eval() evaluates and expression and returns the result
       eval("var res = 100 - 20;") // 80

   11. typeof operator
       typeof variable;
       returns one of: "undefined", "object", "boolean", "number", "string",
                       "function"

   12. delete operator
       deletes a property or a local variable that was not declared with var;
       var o = { x:1, y:2 };
       delete o.x;
       console.log(o);  // { y:2 } <-- x property was removed
================================================================================
