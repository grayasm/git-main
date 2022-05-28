/* Cap.8 Functions
   8.3.2 Variable-Length Argument Lists: The Arguments Object

   $ node 07_args_variable_length.js

   Function that accept any number of arguments are called:
       variadic functions
       variable arity functions, or
       varargs functions

   Within the body of a function, the identifier "arguments" referes to the
   Arguments object of that invocation.
*/

function max(/*...*/){
    var max = Number.NEGATIVE_INFINITY;

    for (var i = 0; i < arguments.length; i++)
        if (arguments[i] > max) max = arguments[i];

    return max;
}

var largest = max(1, 10, 100, 2, 3, 1000, 4, 5, 10000, 6); // => 10000
