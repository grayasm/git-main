/* Cap.8 Functions
   8.8.2 Higher-Order Functions

   $ node 21_example_high_order_functions.js

   A higher-order function is a function that operates on functions,
   taking one or more functions as arguments and returning a new function.
*/


function not(f){
    return function(){                            // Return a new function
        var result = f.apply(this,arguments);     // that calls f
        return !result;                           // and negates its result.
    };
}

var even = function(x) { return x%2 == 0; }
var odd = not(even);

[1,1,3,5,5].every(odd);   // => true: every element of the array is odd
