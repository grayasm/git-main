/* Cap.8
   8.1 Defining Functions

   $ node 01_define_a_function.js

   Use keyword function.
*/


// Print the name and value of each property of o. Return undefined.
function printprops(o){
    for(var p in o)
        console.log(p + ": " + o[p] + "\n");
}

// Compute the distance between Cartesian points (x1,y1) and (x2,y2).
function distance(x1, y1, x2, y2){
    var dx = x2 - x1;
    var dy = y2 - y1;
    return Math.sqrt(dx*dx + dy*dy);
}

// A recursive function that computes factorials.
function factorial(x){
    if (x <= 1) return 1;
    return x * factorial(x-1);
}

// Function expressions can include names, which is useful for recursion.
var f = function fact(x) { if(x <= 1) return 1; else return x*fact(x-1); };

// Function expressions are sometimes defined and immediately invoked:
var tensquared = (function(x){return x*x;}(10));


// Functions may be nested within other functions.
function hypothenuse(a, b){
    function square(x) { return x*x; }
    return Math.sqrt(square(a)+square(b));
}
