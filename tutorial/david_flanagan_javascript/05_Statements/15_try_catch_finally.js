/* Cap.5 Statements
   5.6.6 try/catch/finally

   $ node 15_try_catch_finally.js

   The try/catch/finally statement is JavaScript's exception handling mechanism.

   try {
        // This block can potentially throw an exception.
   }
   catch (e) {
        // This block is executed only if the try block throws an exception.
   }
   finally {
        // This block is executed regardless of what happens in the try block,
        // whether the try block terminates:
        // 1) normally, after reaching the bottom of the block
        // 2) because of a break, continue, or return statement
        // 3) with an exception that is handled by a catch clause above
        // 4) with an uncaught exception that is still propagating
   }
*/



function factorial(x) {

    if (x < 0)
        throw new Error("x must be positive");

    for (var f = 1; x > 1; f *= x, x--) /*empty*/;

    return f;
}

try
{
    console.log("factorial(-1)=", factorial(-1));
}
catch(e)
{
    console.log("----------------exception begin-----------------------------");
    console.log(e);
    console.log("----------------exception end-------------------------------");
}
console.log("exit normal");
/*
----------------exception begin-----------------------------
Error: x must be positive
    at factorial (/home/mihai/Code/git-main/tutorial/david_flanagan_javascript/05_Statements/15_try_catch_finally.js:29:15)
    at Object.<anonymous> (/home/mihai/Code/git-main/tutorial/david_flanagan_javascript/05_Statements/15_try_catch_finally.js:38:35)
    at Module._compile (internal/modules/cjs/loader.js:1015:30)
    at Object.Module._extensions..js (internal/modules/cjs/loader.js:1035:10)
    at Module.load (internal/modules/cjs/loader.js:879:32)
    at Function.Module._load (internal/modules/cjs/loader.js:724:14)
    at Function.executeUserEntryPoint [as runMain] (internal/modules/run_main.js:60:12)
    at internal/main/run_main_module.js:17:47
----------------exception end-------------------------------
exit normal
*/
