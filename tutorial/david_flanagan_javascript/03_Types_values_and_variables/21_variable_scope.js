/* Cap.3 Types, Values and Variables
   3.10  Variable Scope

   $ node 21_variable_scope.js

   The scope of a variable is like in C:
   1. A global variable has global scope.
   2. A local variable has local scope
      - declared in a function body
      - function parameters
      - nested function has its own local scope

   If no "var" is specified:
   3. If a global variable exists its value is modified, otherwise
   4. A new global variable is declared and initialized.
*/


var scope = "global";             // declare a global variable with "var"
function checkscope() {
    var scope = "local";          // declare a local variable with "var"
    return scope;
};
console.log(  checkscope()  );    // "local"


_scope = "global";                // declare a global variable even without "var"
function checkscope2() {
    _scope = "local";             // Oops! the global _scope is modified.
    myscope = "local";            // declare a new global variable
    return null;
};
checkscope2();

console.log(  _scope  );          // "local"
console.log(  myscope );          // "local"


// Nested function has its own local scope.
var scope = "global scope";
function checkscope() {
    var scope = "local scope";
    function nested() {
        var scope = "nested scope";
        return scope;
    };
    return nested();
};
console.log(  checkscope()  );    // "nested scope"
