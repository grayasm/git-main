/* Cap.5 Statements
   5.3.2 function

   $ node 02_function.js

   A function declaration statement has the following syntax:

   function funcname([arg1 [, arg2 [..., argn]]]) {
       statements
   }
*/

var f = function(x) { return x + 1; } // Expression assigned to a variable
function f(x) { return x + 1; }

function hypotenuse(x, y) {
    return Math.sqrt(x*x + y*y);
}

function factorial(n) {               // A recursive function
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}


var s = sum(10);                      // Function sum declaration is hoisted up
console.log('s=', s);                 // s=55

function sum(n) {                     // 'sum' function is available before
    if (n <= 1) return 1;             // declaration
    return n + sum(n - 1);
}
