/* Cap.8 Functions
   8.8.4 Memoization

   $ node 23_example_memoization.js

   In functional programming, a function that cached its previously computed
   results is called memoization.

   The code below shows a higher-order function, memoize() that accepts
   a function as its argument and returns a memoized version of the function.
*/

function memoize(f){
    var cache = {};
    return function(){
        var key = arguments.length + Array.prototype.join.call(arguments,",");
        if (key in cache) return cache[key];
        else return cache[key] = f.apply(this, arguments);
    };
}

// Return the Greatest Common Divizor of two integers, using the Euclidian algo.
// https://en.wikipedia.org/wiki/Euclidean_algorithm
function gcd(a,b){
    var t;
    if (a < b) t=b, b=a, a=t;
    while(b != 0) t=b, b=a%b; a=t;
    return a;
}

var gcdmemo = memoize(gcd);
gcddemo(85, 187); // => 17
