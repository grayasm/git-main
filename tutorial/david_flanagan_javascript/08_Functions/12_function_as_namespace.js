/* Cap.8
   8.5 Functions As Namespaces

   $ node 12_function_as_namespace.js

   Variables declared within a function are visible throughout the function
   (including within nested functions) but do not exist outside of the function.

   It is sometimes useful to define a function simply to act as a temporary
   namespace in which you can define variables without polluting the global
   namespace.
*/

function mymodule() {
    // Module code goes here.
    // Any variable used by the module are local to this function.
}
mymodule();


// mymodule() written and invoked as an unnamed expression:

(function() {
    // Module code goes here.
}());
