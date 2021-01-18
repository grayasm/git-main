/* Cap.5 Statements
   5.3.1 var

   $ node 01_var.js

   The var statement declares a variable or variables. Here's the syntax:

   var name_1 [ = value_1] [, ... , name_n [ = value_n ]]

   > on top-level code var declares global variables
   > in the body of a function var declares local variables
   > the declaration is "hoisted" up to the start of the script or function
   > the var statement in a for loop is "hoisted" outside of the loop
   > var can declare the same variable multiple times
   > properties created with var cannot be deleted
*/

var i;                                        // one simple variable
var j = 0;
var p, q;
var name = "Henry";
var greeting = "Hello " + name;               // a complex initializer
var x = 2.34, y = Math.cos(0.75), r, theta;   // many variables
var x = 2, y = x * x;                         // second var uses the first
var x = 2,                                    // multiple variables
    f = function(x) { return x*x; },          // each on its own line
    y = f(x);

console.log('y=', y);   // y=4


for (var k = 0; k < 10; k++){ }
console.log('k=', k);   // k=10  <-- hoisted outside for loop
