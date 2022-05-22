/* Cap.8
   8.2.1 Function Invocation

   $ node 02_invoke_function.js

*/

function printprops(o){
    for(var p in o)
        console.log(p + ": " + o[p] + "\n");
}

// Invoke the function 'printprops'
printprops( {x:1} );  // => x: 1

// Function do not typically use the 'this' keyword. It can be used however
// to determine whether strict mode is in effect:
var strict = (function() { return !this; }());      // => false
