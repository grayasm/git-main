/* Cap.8 Functions
   8.3.4 Argument Types

   $ node 09_args_types.js


   JavaScript method parameters have no declared types, and no type checking is
   performed on the values you pass to a function.

   Unless you are writing a “throwaway” function that will be called only once
   or twice, it may be worth adding code to check the types of arguments like
   this.
*/

function isArrayLike(o) {
    if (o &&                                    // o is not null, undefined, etc
        typeof o === "object" &&                // o is an object
        isFinite(o.length) &&                   // o.length is a finite number
        o.length >= 0 &&                        // o.length is non-negative
        o.length === Math.floor(o.length) &&    // o.length is an integer
        o.length < 424967296)                   // o.length < 2^32
        return true;                            // Then o is Array like
    else
        return false;                           // Otherwise it is not.
}

function sum(a) {
    if (isArrayLike(a)){
        var total = 0;
        for (var i = 0; i < a.length; i++){
            var element = a[i];
            if (element == null) continue;
            if (isFinite(element)) total += element;
            else throw new Error("sum(): elements must be finite numbers");
        }
        return total;
    }
    else throw new Error("sum(): arguments must be array-like");
}

var b = sum([1,2,3,4,5,null,undefined]);  // => b = 15
