/* Cap.4 Expressions and Operators
   4.12.2 Global eval()

   $ node 22_eval_global.js

   eval() can change local variables.
   eval() can no longer change global variables when it is called via alias.
      see: var geval = eval;
*/

var x = "global";
var y = "global";

var geval = eval;

function f() {
    var x = "local";
    eval("x += '-changed';");   // <-- Chrome browser will throw exception
    return x;
}

function g() {
    var y = "local";
    geval("y += '-changed';");  // <-- Node.js ReferenceError: y is not defined
    return y;
}

console.log( f() );
console.log( g() );
