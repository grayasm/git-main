/* Cap.4 Expressions and Operators
   4.10.1 Logical AND (&&)

   $ node 17_logical_AND.js

   The && can be understood at three levels:
    - when used with boolean operands
    - when used with "truthy" values
    - when used as "short circuiting"
*/


// with boolean values
var x = y = 0;
console.log(  x == 0 && y == 0  );  // true


// "truthy" and "falsy"
// falsy values are: false, null, undefined, 0, -0, NaN and ""
var o = { x:1 };
var p = null;

console.log ( o && o.x );  // 1: o is truthy, so return value of o.x
console.log ( p && p.x );  // null: p is falsy, so return it and don't evaluate p.x


// "short circuiting"
var a = b = 5;
var stop = function() { console.log("stop"); }

if (a == b) stop();        // "stop": Invoke stop() only if a == b
(a == b) && stop();        // "stop": This does the same thing
