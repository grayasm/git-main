/* Cap.8
   8.7.1 The length Property

   $ node 14_prop_length.js

   Within the body of a function, arguments.length specifies the number of
   arguments that were passed to the function.
*/

function check(args){
    var actual = args.length;             // The actual number of arguments
    var expected = args.callee.length;    // The expected number of arguments
    if (actual !== expected)
        throw new Error("Expected " + expected + " args; got " + actual);
}

function f(x, y, z){
    check(arguments);                     // Check that the # args matches.
    return x + y + z;                     // Now do the rest normally.
}
