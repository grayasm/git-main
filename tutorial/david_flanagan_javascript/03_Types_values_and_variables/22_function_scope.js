/* Cap.3 Types, Values and Variables
   3.10.1  Function Scope and Hoisting

   $ node 22_function_scope.js

   The block scope as we know it from C behaves differently in JavaScript.
     -  a local variable to a function body is visible also above the place
        of declaration (hoisting)
     -  a local variable to a nested function body is visible in the outer body
*/

// Example: JavaScript does not have the concept of block scope.

function test(o) {
    var i = o;                        // i is defined throughout function

    if (typeof o == "object") {
        var j = o;                    // j is defined everywhere, not just block
        for (var k = 0; k < 10; k++){ // k is defined everywhere, not just block
            console.log(k);           // print numbers 0 through 9
        } // for(k)

        console.log(k)                // k is still defined: prints 10
    } // o == object

    console.log(j);                   // j is defined, but may not be initialized
} // test(o)

test([0]);
/* output:
0
1
2
3
4
5
6
7
8
9
10
[ 0 ]
*/

// Example: Not any associated assighments are "hoisted"

var scope = "global";
function f() {

    console.log(scope);    // Prints "undefined", not "global"
    var scope = "local";   // Variable initialized here, but defined everywhere
    console.log(scope);    // Prints "local"
} // f()

f();
/* output:
undefined
local
*/
